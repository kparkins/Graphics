#include "matrix_transform.h"

gfx::matrix_transform::matrix_transform() {
    m_material = material_factory::get("white");
}

gfx::matrix_transform::~matrix_transform() {

}

void gfx::matrix_transform::draw(mat4 &c) {
    mat4 trans = c * m_transform;
    for(auto child : m_children) {
        child->draw(trans);
    }
}

