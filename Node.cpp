#include "Node.h"

Node::Node() {
    memset(static_cast<void*>(&m_boundingSphere), 0, sizeof(BoundingSphere));
    m_bs = false;
    m_cull = false;
}

Node::~Node() {

}

BoundingSphere Node::getBoundingSphere() {
    return this->m_boundingSphere;
}

void Node::drawBoundingSphere() {
    Matrix4 trans;
    trans.makeTranslate(m_boundingSphere.origin);
    glPushMatrix();
    glLoadIdentity();
    glMultMatrixf(trans.ptr());
    glutWireSphere(m_boundingSphere.radius, 30, 30);
    glPopMatrix();
}
