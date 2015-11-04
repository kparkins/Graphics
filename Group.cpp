#include "Group.h"

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
    for(auto child : m_children) {
        child->draw(c);
    }
}
