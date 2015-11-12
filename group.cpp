#include "group.h"

gfx::group::group() {

}

gfx::group::~group() {
    m_children.clear();
}

void gfx::group::add(node_ptr child) {
    m_children.push_back(child);
}

void gfx::group::remove(node_ptr child) {
    auto it = find(m_children.begin(), m_children.end(), child);
    if(it != m_children.end()) {
        m_children.erase(it);
    }
}

void gfx::group::draw(mat4 & c) {
    for(auto child : m_children) {
        child->draw(c);
    }
}

