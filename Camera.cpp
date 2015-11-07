#include "camera.h"

gfx::camera::camera() {
    this->reset();
}

void gfx::camera::reset() {
    m_matrix.identity();
    m_center.set(0.0, 0.0, 20.0);
    m_lookat.set(0.0, 0.0, 0.0);
    m_up.set(0.0, 1.0, 0.0);
    m_fov = static_cast<float>(60.f * M_PI / 180.f);

    //Pre-define a camera matrix (and its inverse) that are shifted 'e' from the origin
    //This is used as a default camera m_position for Project 1
    m_matrix.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, m_center[0], m_center[1], m_center[2], 1);
    m_inverse.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -m_center[0], -m_center[1], -m_center[2], 1);
}

gfx::camera::~camera() {
    //Delete and dynamically allocated memory/objects here
}

mat4 & gfx::camera::matrix() {
    return m_matrix;
}

mat4 & gfx::camera::inverse_matrix() {
    return m_inverse;
}

void gfx::camera::update() {
    vec3 & z = (m_center - m_lookat).normalize();
    vec3 & x = m_up.cross(z).normalize();
    vec3 & y = z.cross(x).normalize();

    _mm_store_ps(m_matrix[0], _mm_load_ps(x.ptr()));
    _mm_store_ps(m_matrix[1], _mm_load_ps(y.ptr()));
    _mm_store_ps(m_matrix[2], _mm_load_ps(z.ptr()));
    _mm_store_ps(m_matrix[3], _mm_load_ps(m_center.ptr()));

    m_matrix[3][3] = 1.f;
    m_inverse = m_matrix.rigid_inverse();
}
 
void gfx::camera::set(vec3 & e, vec3 & d, vec3 & up) {
    this->m_center = e;
    this->m_lookat = d;
    this->m_up = up;
    this->update();
}

void gfx::camera::set(float fov) {
    this->m_fov = fov;
}