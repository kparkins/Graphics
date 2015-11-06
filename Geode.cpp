#include "Geode.h"
#include "Globals.h"

Geode::Geode() {
    m_material = MaterialFactory::material("polished gold");
}

Geode::~Geode() {

}

void Geode::draw(Matrix4 &c) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(c.ptr());
    m_material.apply();
    this->render();

    if(m_bs && Globals::drawBoundingSphere) {
        Matrix4 trans;
        trans.makeTranslate(0.f, -.45f, 0.f);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glMultMatrixf(trans.ptr());
        glutWireSphere(m_boundingSphere.radius, 10, 10);
        glPopMatrix();
    }
    glPopMatrix();
}

void Geode::update(float dt) {

}

