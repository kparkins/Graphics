#include "Vector3.h"
#include "Vector4.h"

Vector3::Vector3() {
    m[0] = 0;
    m[1] = 0;
    m[2] = 0;
}

Vector3::Vector3(float m0, float m1, float m2) {
    m[0] = m0;
    m[1] = m1;
    m[2] = m2;
}

Vector3::~Vector3() {
    //
}

float* Vector3::ptr() {
    return &m[0];
}

void Vector3::set(float x, float y, float z) {
    m[0] = x;
    m[1] = y;
    m[2] = z;
}

void Vector3::set(int index, float value) {
    m[index] = value;
}

float& Vector3::operator [] (int loc) {
    return m[loc];
}

Vector3 Vector3::add(Vector3 a) {
    return Vector3(m[0] + a[0], m[1] + a[1], m[2] + a[2]);
}

Vector3 Vector3::operator + (Vector3 a) {
    return this->add(a);
}

Vector3 Vector3::subtract(Vector3 a) {
    return Vector3(m[0] - a[0], m[1] - a[1], m[2] - a[2]);
}

Vector3 Vector3::operator-(Vector3 a) {
    return this->subtract(a);
}

Vector3 Vector3::negate(void) {
     return this->multiply(-1); 
}

Vector3 Vector3::scale(float s) {
    return this->multiply(s);
}

Vector3 Vector3::multiply(float a) {
    return Vector3(m[0] * a, m[1] * a, m[2] * a);
}

Vector3 Vector3::operator * (float a) {
    return this->multiply(a);
}

Vector3 Vector3::multiply(Vector3 a) {
    return Vector3(m[0] * a[0], m[1] * a[1], m[2] * a[2]);
}

Vector3 Vector3::operator * (Vector3 a) {
    return this->multiply(a);
}

float Vector3::dot(Vector3 a) {
    return m[0] * a[0] + m[1] * a[1] + m[2] * a[2];
}

Vector3 Vector3::cross(Vector3 a) {
    return Vector3(m[1] * a[2] - m[2] * a[1], 
                  (m[2] * a[0] - m[0] * a[2]),
                   m[0] * a[1] - m[1] * a[0]);
}

float Vector3::angle(Vector3 a) {
    float m1 = this->magnitude();
    float m2 = a.magnitude();
    if (m1 > 0.f && m2 > 0.f) {
        return acosf(this->dot(a) / (m1 * m2));
    }
    return 0.f;
}

float Vector3::magnitude(void) {
    return sqrt(m[0] * m[0] + m[1] * m[1] + m[2] * m[2]);
}

Vector3 Vector3::normalize(void) {
    float magnitude = this->magnitude();
    return (magnitude) 
      ? Vector3(m[0] / magnitude, m[1] / magnitude, m[2] / magnitude) 
      : Vector3(0.f, 0.f, 0.f);
}

Vector4 Vector3::toVector4(float w) {
    return Vector4(m[0], m[1], m[2], w);
}

void Vector3::print(std::string comment) {
    std::cout << comment << std::endl;
    std::cout << "<x:" << m[0] <<  ", y:" << m[1] << ", z:" << m[2] << ">" << std::endl;
}
