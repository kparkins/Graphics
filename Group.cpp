#include "Group.h"
#include "Globals.h"
#include "Window.h"

Group::Group() {

}

Group::~Group() {
    m_children.clear();
}

void Group::addChild(NodePtr child) {
    m_children.push_back(child);
}

void Group::removeChild(NodePtr child) {
    auto it = find(m_children.begin(), m_children.end(), child);
    if(it != m_children.end()) {
        m_children.erase(it);
    }
}

void Group::draw(Matrix4 & c) {
    Vector4 v(0.f, 0.f, 0.f, 1.f);
    m_boundingSphere.origin = (c * v).toVector3();
    if(Globals::enableCulling && !Window::frustrum.sphereInFrustrum(m_boundingSphere.origin, m_boundingSphere.radius)) {
       return;
    }
    for(auto child : m_children) {
        child->draw(c);
    }
    if(Globals::drawBoundingSphere && m_bs) {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glMultMatrixf(c.ptr());
        Matrix4 trans;
        trans.makeTranslate(0.f, -.45f, 0.f);
        glPushMatrix();
        glMultMatrixf(trans.ptr());
        glutWireSphere(m_boundingSphere.radius, 10, 10);
        glPopMatrix();
    }
}

void Group::update(float dt) {

}
