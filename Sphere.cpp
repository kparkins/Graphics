#include "Sphere.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


Sphere::Sphere(double radius, int slices, int stacks) : Drawable() {
    this->radius = radius;
    this->slices = slices;
    this->stacks = stacks;
    this->velocity = Vector3(30.f, 40.f, 50.f);
}

void Sphere::draw(DrawData& data) {
    material.apply();
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    glutSolidSphere(radius, slices, stacks);
    
    glPopMatrix();
}


void Sphere::update(UpdateData& data) {
    Matrix4 translate;
    
    translate.makeTranslate(velocity * data.dt);
    
    toWorld = translate * toWorld;
    
    Vector3 position(toWorld[3][0], toWorld[3][1], toWorld[3][2]);
    
    if(position.x() < -6 || position.x() > 6) {
        velocity.x() *= -1.f;
    }
    
    if(position.y() < -6 || position.y() > 6) {
        velocity.y() *= -1.f;
    }
    
    if(position.z() < -5.1 || position.z() > 5.1) {
        velocity.z() *= -1.f;
    }
    
    velocity.y() += -.25f;
    velocity = velocity * .992;
    
    if (velocity.magnitude() < .1) {
        velocity.multiply(0.f);
    }
}


