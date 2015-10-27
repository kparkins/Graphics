#include "Camera.h"

Camera::Camera() {
    this->reset();
}

void Camera::reset() {
    c.identity();
    e.set(0.0, 0.0, 20.0);
    d.set(0.0, 0.0, 0.0);
    up.set(0.0, 1.0, 0.0);
    fov = static_cast<float>(60.f * M_PI / 180.f);

    //Pre-define a camera matrix (and its inverse) that are shifted 'e' from the origin
    //This is used as a default camera m_position for Project 1
    c.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, e[0], e[1], e[2], 1);
    ci.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -e[0], -e[1], -e[2], 1);
}

Camera::~Camera() {
    //Delete and dynamically allocated memory/objects here
}

Matrix4& Camera::getMatrix() {
    return c;
}

Matrix4& Camera::getInverseMatrix() {
    return ci;
}

void Camera::update() {
    Vector3 & z = (e - d).normalize();
    Vector3 & x = up.cross(z).normalize();
    Vector3 & y = z.cross(x).normalize();

    _mm_store_ps(c[0], _mm_load_ps(x.ptr()));
    _mm_store_ps(c[1], _mm_load_ps(y.ptr()));
    _mm_store_ps(c[2], _mm_load_ps(z.ptr()));
    _mm_store_ps(c[3], _mm_load_ps(e.ptr()));

    c[3][3] = 1.f;
    ci = c.rigidInverse();
}
 
void Camera::set(Vector3& e, Vector3& d, Vector3& up) {
    this->e = e;
    this->d = d;
    this->up = up;
    this->update();
}
