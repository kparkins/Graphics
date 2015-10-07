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

Vector4 Vector4::dehomogenize() const {
    if (!w) {
        return *this;
    }
    Vector4 b;
    _mm_store_ps(b.ptr(), _mm_div_ps(_mm_load_ps(&x), _mm_set1_ps(w)));
    b.w = 1.f;
    return b;
}

float Vector4::dot(const Vector4 & a) const {
    float res;
    __m128 r = _mm_mul_ps(_mm_load_ps(&x), _mm_load_ps(&a.x));
    r = _mm_hadd_ps(r, r);
    r = _mm_hadd_ps(r, r);
    _mm_store_ss(&res, r);
    return res;
}
