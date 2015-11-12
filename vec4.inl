#include "vec4.h"

gfx::vec4& gfx::vec4::set(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
    return *this;
}

float* gfx::vec4::ptr() {
    return &x;
}

float& gfx::vec4::operator[](int loc) {
    return (&x)[loc];
}

gfx::vec4 gfx::vec4::add(const gfx::vec4 & a) const {
    vec4 b;
    _mm_store_ps(&b.x, _mm_add_ps(_mm_load_ps(&x), _mm_load_ps(&a.x)));
    return b;
}

gfx::vec4 gfx::vec4::operator+(const gfx::vec4 & a) const {
    vec4 b;
    _mm_store_ps(&b.x, _mm_add_ps(_mm_load_ps(&x), _mm_load_ps(&a.x)));
    return b;
}

gfx::vec4 gfx::vec4::subtract(const gfx::vec4 & a) const {
    vec4 b;
    _mm_store_ps(&b.x, _mm_sub_ps(_mm_load_ps(&x), _mm_load_ps(&a.x)));
    return b;
}

gfx::vec4 gfx::vec4::operator-(const gfx::vec4 & a) const {
    vec4 b;
    _mm_store_ps(&b.x, _mm_sub_ps(_mm_load_ps(&x), _mm_load_ps(&a.x)));
    return b;
}

gfx::vec4& gfx::vec4::dehomogenize() {
    if (!w) {
        return *this;
    }
    _mm_store_ps(&x, _mm_div_ps(_mm_load_ps(&x), _mm_set1_ps(w)));
    w = 1.f;
    return *this;
}

float gfx::vec4::dot(const gfx::vec4 & a) const {
    float res;
    __m128 r = _mm_mul_ps(_mm_load_ps(&x), _mm_load_ps(&a.x));
    r = _mm_hadd_ps(r, r);
    r = _mm_hadd_ps(r, r);
    _mm_store_ss(&res, r);
    return res;
}

gfx::vec4& gfx::vec4::normalize() {
    float denom = x * x + y * y + z * z;
    x /= denom;
    y /= denom;
    z /= denom;
    return *this;
}