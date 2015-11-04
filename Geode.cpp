#include "Geode.h"

Geode::Geode() {
    MaterialFactory factory;
    m_material = factory.make("polished gold");
}

Geode::~Geode() {

}

void Geode::draw(Matrix4 &c) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(c.ptr());
    m_material.apply();
    this->render();
    glPopMatrix();
}

