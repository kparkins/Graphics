#include "vec4.h"

Vector4& Vector4::set(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
    return *this;
}

float* Vector4::ptr() {
    return &x;
}

float& Vector4::operator[](int loc) {
    return (&x)[loc];
}

Vector4 Vector4::add(const Vector4 & a) const {
    Vector4 b;
    _mm_store_ps(&b.x, _mm_add_ps(_mm_load_ps(&x), _mm_load_ps(&a.x)));
    return b;
}

Vector4 Vector4::operator+(const Vector4 & a) const {
    Vector4 b;
    _mm_store_ps(&b.x, _mm_add_ps(_mm_load_ps(&x), _mm_load_ps(&a.x)));
    return b;
}

Vector4 Vector4::subtract(const Vector4 & a) const {
    Vector4 b;
    _mm_store_ps(&b.x, _mm_sub_ps(_mm_load_ps(&x), _mm_load_ps(&a.x)));
    return b;
}

Vector4 Vector4::operator-(const Vector4 & a) const {
    Vector4 b;
    _mm_store_ps(&b.x, _mm_sub_ps(_mm_load_ps(&x), _mm_load_ps(&a.x)));
    return b;
}

Vector4& Vector4::dehomogenize() {
    if (!w) {
        return *this;
    }
    _mm_store_ps(&x, _mm_div_ps(_mm_load_ps(&x), _mm_set1_ps(w)));
    w = 1.f;
    return *this;
}

float Vector4::dot(const Vector4 & a) const {
    float res;
    __m128 r = _mm_mul_ps(_mm_load_ps(&x), _mm_load_ps(&a.x));
    r = _mm_hadd_ps(r, r);
    r = _mm_hadd_ps(r, r);
    _mm_store_ss(&res, r);
    return res;
}
