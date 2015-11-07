#include "geode.h"

gfx::geode::geode() {
    m_material = material_factory::material("polished gold");
}

gfx::geode::~geode() {

}

void gfx::geode::draw(mat4 &c) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(c.ptr());
    apply(m_material);
    this->render();
    glPopMatrix();
}


