#include "Vector4.h"

void Vector4::set(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

float* Vector4::ptr() {
    return &x;
}

float& Vector4::operator[](int loc) {
    return (&x)[loc];
}

Vector4 Vector4::add(const Vector4 & a) const {
    Vector4 b;
    __m128 a0 = _mm_load_ps(&a.x);
    __m128 m0 = _mm_load_ps(&x);
    _mm_store_ps(&b.x, _mm_add_ps(m0, a0));
    return b;
}

Vector4 Vector4::operator+(const Vector4 & a) const {
    Vector4 b;
    __m128 a0 = _mm_load_ps(&a.x);
    __m128 m0 = _mm_load_ps(&x);
    _mm_store_ps(&b.x, _mm_add_ps(m0, a0));
    return b;
}

Vector4 Vector4::subtract(const Vector4 & a) const {
    Vector4 b;
    __m128 a0 = _mm_load_ps(&a.x);
    __m128 m0 = _mm_load_ps(&x);
    _mm_store_ps(&b.x, _mm_sub_ps(m0, a0));
    return b;
}

Vector4 Vector4::operator-(const Vector4 & a) const {
    Vector4 b;
    __m128 a0 = _mm_load_ps(&a.x);
    __m128 m0 = _mm_load_ps(&x);
    _mm_store_ps(&b.x, _mm_sub_ps(m0, a0));
    return b;
}

Vector4 Vector4::dehomogenize() const {
    if(!w) {
        return *this;
    }
    Vector4 b;
    __m128 m0 = _mm_load_ps(&x);
    __m128 w0 = _mm_set1_ps(w);
    _mm_store_ps(b.ptr(), _mm_div_ps(m0, w0));
    b.w = 1.f;
    return b;
}

float Vector4::dot(const Vector4 & a) const {
    return (x * a.x) + (y * a.y) + (z * a.z) + (w * a.w);
}
