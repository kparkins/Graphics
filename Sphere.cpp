#include "Sphere.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


Sphere::Sphere(double radius, int slices, int stacks) : Drawable() {
    this->m_radius = radius;
    this->m_slices = slices;
    this->m_stacks = stacks;
    this->m_velocity = Vector3(30.f, 40.f, 50.f);
}

void Sphere::draw(DrawData& data) {
    m_material.apply();
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(m_toWorld.ptr());
    
    glutSolidSphere(m_radius, m_slices, m_stacks);
    
    glPopMatrix();
}


void Sphere::update(UpdateData& data) {
    m_toWorld = Matrix4().makeTranslate(m_velocity * data.m_dt) * m_toWorld;
    
    Vector3 position(m_toWorld[3][0], m_toWorld[3][1], m_toWorld[3][2]);

    if(position.x < -6 || position.x > 6) {
        m_velocity.x *= -1.f;
    }
    
    if(position.y < -6 || position.y > 6) {
        m_velocity.y *= -1.f;
    }
    
    if(position.z < -5.1 || position.z > 5.1) {
        m_velocity.z *= -1.f;
    }
    
    m_velocity.y += -.25f;
    m_velocity = m_velocity * .992;
    
    if (m_velocity.magnitude() < .1) {
        m_velocity.multiply(0.f);
    }
}


