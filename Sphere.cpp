#include "Sphere.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include <mutex>

Sphere::Sphere(double radius, int slices, int stacks) : Drawable() {
    this->m_radius = radius;
    this->m_slices = slices;
    this->m_stacks = stacks;
}

void Sphere::setRadius(double radius) {
    this->m_radius = radius;
}

void Sphere::setSlices(int slices) {
    this->m_slices = slices;
}

void Sphere::setStacks(int stacks) {
    this->m_stacks = stacks;
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
    //
}


