#include "geode.h"

gfx::geode::geode() {
    m_usematerial = true;
    m_material = material_factory::get("polished gold");
}

gfx::geode::~geode() {

}

void gfx::geode::draw(mat4 &c) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(c.ptr());
    if(m_usematerial) {
        apply(m_material);
    }
    this->render();
    glPopMatrix();
}


