#include "MatrixTransform.h"
#include "MaterialFactory.h"
#include "Window.h"

MatrixTransform::MatrixTransform() {
    m_material = MaterialFactory::material("white");
}

MatrixTransform::~MatrixTransform() {

}

void MatrixTransform::draw(Matrix4 &c) {
    Matrix4 trans = c * m_transform;

    Vector4 v(0.f, 0.f, 0.f, 1.f);
    m_boundingSphere.origin = ((trans * v)).toVector3();


    for(auto child : m_children) {
        child->draw(trans);
    }
    if(m_bs && Globals::drawBoundingSphere) {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glMultMatrixf(c.ptr());
        m_material.apply();
        glutWireSphere(m_boundingSphere.radius, 10, 10);
        glPopMatrix();
    }
}

void MatrixTransform::setTransform(const Matrix4 & transform) {
    this->m_transform = transform;
}

Matrix4& MatrixTransform::getTransform() {
    return this->m_transform;
}
