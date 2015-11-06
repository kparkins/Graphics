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
    m_c = c;
    m_material.apply();
    this->render();

    if(m_bs && Globals::drawBoundingSphere) {
        Vector4 v(0.f, 0.f, 0.f, 1.f);
        Matrix4 trans;
        trans.makeTranslate(0.f, -.45f, 0.f);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glMultMatrixf(trans.ptr());
        glutWireSphere(m_boundingSphere.radius, 10, 10);
        m_boundingSphere.origin = ((c * trans) * v).toVector3() ;
        glPopMatrix();
    }
    glPopMatrix();
}

void Geode::update(float dt) {

}

