#include "MatrixTransform.h"

MatrixTransform::MatrixTransform() {

}

MatrixTransform::~MatrixTransform() {

}

void MatrixTransform::draw(Matrix4 &c) {
    Matrix4 trans = c * m_transform;
    for(auto child : m_children) {
        child->draw(trans);
    }
}

void MatrixTransform::setTransform(const Matrix4 & transform) {
    this->m_transform = transform;
}

Matrix4& MatrixTransform::getTransform() {
    return this->m_transform;
}