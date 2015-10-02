#include "Vector4.h"

float& Vector4::x() {
    return m[0];
}

float& Vector4::y() {
    return m[1];
}

float& Vector4::z() {
    return m[2];
}

float& Vector4::w() {
    return m[3];
}

float* Vector4::ptr() {
    return &m[0];
}

void Vector4::set(float x, float y, float z, float w) {
    m[0] = x;
    m[1] = y;
    m[2] = z;
    m[3] = w;
}

float& Vector4::operator[](int loc) {
    return m[loc];
}

Vector4 Vector4::add(Vector4& a) {
    return Vector4(m[0] + a[0], m[1] + a[1], m[2] + a[2], m[3] + a[3]);
}

Vector4 Vector4::operator+(Vector4 a) {
    return this->add(a);
}

Vector4 Vector4::subtract(Vector4& a) {
    return Vector4(m[0] - a[0], m[1] - a[1], m[2] - a[2], m[3] - a[3]);
}

Vector4 Vector4::operator-(Vector4 a) {
    return this->subtract(a);
}

Vector4 Vector4::dehomogenize() {
    if(!m[3]) {
        return Vector4(m[0], m[1], m[2], 0);
    }
    return Vector4(m[0] / m[3], m[1] / m[3], m[2] / m[3], 1.f);
}

float Vector4::dot(Vector4 a) {
    return (m[0] * a.m[0]) + (m[1] * a.m[1]) + (m[2] * a.m[2]) + (m[3] * a.m[3]);
}

void Vector4::print(std::string comment) {
    std::cout << comment << std::endl;
    std::cout << "<x:" << m[0] <<  ", y:" << m[1] << ", z:" << m[2] << ", w:" << m[3] << ">" << std::endl;
}
