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