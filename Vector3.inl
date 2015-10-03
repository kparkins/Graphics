#include "Vector3.h"


void Vector3::set(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

float& Vector3::operator[](int loc) {
    return (&x)[loc];
}

float* Vector3::ptr() {
    return &x;
}

Vector3& Vector3::operator*=(const Vector3 & a) {
    __m128 m0 = _mm_load_ps(&x);
    __m128 a0 = _mm_load_ps(&a.x);
    _mm_store_ps(&x, _mm_mul_ps(m0, a0));
    return *this;
}

Vector3& Vector3::operator+=(const Vector3 & a) {
    __m128 m0 = _mm_load_ps(&x);
    __m128 a0 = _mm_load_ps(&a.x);
    _mm_store_ps(&x, _mm_add_ps(m0, a0));
    return *this;
}

Vector3& Vector3::operator-=(const Vector3 & a) {
    __m128 m0 = _mm_load_ps(&x);
    __m128 a0 = _mm_load_ps(&a.x);
    _mm_store_ps(&x, _mm_sub_ps(m0, a0));
    return *this;
}

Vector3& Vector3::operator=(const Vector3 & a) {
    __m128 a0 = _mm_load_ps(&a.x);
    _mm_store_ps(&x, a0);
    return *this;
}

Vector3& Vector3::operator*=(float s) {
    __m128 s0 = _mm_set1_ps(s);
    __m128 m0 = _mm_load_ps(&x);
    _mm_store_ps(&x, _mm_mul_ps(m0, s0));
    return *this;
}

Vector3& Vector3::operator+=(float s) {
    __m128 s0 = _mm_set1_ps(s);
    __m128 m0 = _mm_load_ps(&x);
    _mm_store_ps(&x, _mm_add_ps(m0, s0));
    return *this;
}

Vector3& Vector3::operator-=(float s) {
    __m128 s0 = _mm_set1_ps(s);
    __m128 m0 = _mm_load_ps(&x);
    _mm_store_ps(&x, _mm_sub_ps(m0, s0));
    return *this;
}

Vector3& Vector3::operator=(float s) {
    __m128 s0 = _mm_set1_ps(s);
    _mm_store_ps(&x, s0);
    return *this;
}

Vector3 Vector3::operator+(const Vector3& a) const {
    Vector3 b;
    __m128 a0 = _mm_load_ps(&a.x);
    __m128 m0 = _mm_load_ps(&x);
    _mm_store_ps(&b.x, _mm_add_ps(m0, a0));
    return b;
}

Vector3 Vector3::add(const Vector3 & a) const {
    return (*this) + a;
}

Vector3 Vector3::operator-(const Vector3 & a) const {
    Vector3 b;
    __m128 a0 = _mm_load_ps(&a.x);
    __m128 m0 = _mm_load_ps(&x);
    _mm_store_ps(&b.x, _mm_sub_ps(m0, a0));
    return b;
}

Vector3 Vector3::subtract(const Vector3 & a) const {
    return (*this) - a;
}

Vector3 Vector3::operator*(float a) const {
    Vector3 b;
    __m128 m0 = _mm_load_ps(&x);
    __m128 a0 = _mm_set1_ps(a);
    _mm_store_ps(&b.x, _mm_mul_ps(m0, a0));
    return b;
}

Vector3 Vector3::negate(void) const {
    return (*this) * -1.f;
}

Vector3 Vector3::scale(float s) const {
    return (*this) * s;
}

Vector3 Vector3::multiply(float a) const {
    return (*this) * a;
}

Vector3 Vector3::operator*(const Vector3 & a) const {
    Vector3 b;
    __m128 m0 = _mm_load_ps(&x);
    __m128 a0 = _mm_load_ps(&a.x);
    _mm_store_ps(&b.x, _mm_mul_ps(m0, a0));
    return b;
}

Vector3 Vector3::multiply(const Vector3 & a) const {
    return (*this) * a;
}

float Vector3::dot(const Vector3 & a) const {
    return x * a.x + y * a.y + z * a.z;
}

Vector3 Vector3::cross(const Vector3 & a) const {
    return Vector3(y * a.z - z * a.y,
                  (z * a.x - x * a.z),
                   x * a.y - y * a.x);
}

float Vector3::angle(const Vector3 & a) const {
    float m1 = this->magnitude();
    float m2 = a.magnitude();
    if (m1 > 0.f && m2 > 0.f) {
        return acosf(this->dot(a) / (m1 * m2));
    }
    return 0.f;
}

float Vector3::magnitude(void) const {
    return sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::normalize(void) const {
    float magnitude = this->magnitude();
    return (magnitude)
    ? Vector3(x / magnitude, y / magnitude, z / magnitude)
    : Vector3(0.f, 0.f, 0.f);
}
