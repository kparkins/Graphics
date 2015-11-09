#include "vec3.h"


void gfx::vec3::set(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

float& gfx::vec3::operator[](int loc) {
    return (&x)[loc];
}

float* gfx::vec3::ptr() {
    return &x;
}

gfx::vec3& gfx::vec3::operator*=(const vec3 & a) {
    _mm_store_ps(&x, _mm_mul_ps(_mm_load_ps(&x), _mm_load_ps(&a.x)));
    return *this;
}

gfx::vec3& gfx::vec3::operator+=(const vec3 & a) {
    _mm_store_ps(&x, _mm_add_ps(_mm_load_ps(&x), _mm_load_ps(&a.x)));
    return *this;
}

gfx::vec3& gfx::vec3::operator-=(const vec3 & a) {
    _mm_store_ps(&x, _mm_sub_ps(_mm_load_ps(&x), _mm_load_ps(&a.x)));
    return *this;
}

gfx::vec3& gfx::vec3::operator=(const vec3 & a) {
    _mm_store_ps(&x, _mm_load_ps(&a.x));
    return *this;
}

gfx::vec3& gfx::vec3::operator*=(float s) {
    _mm_store_ps(&x, _mm_mul_ps(_mm_load_ps(&x), _mm_set1_ps(s)));
    return *this;
}

gfx::vec3& gfx::vec3::operator+=(float s) {
    _mm_store_ps(&x, _mm_add_ps(_mm_load_ps(&x), _mm_set1_ps(s)));
    return *this;
}

gfx::vec3& gfx::vec3::operator-=(float s) {
    _mm_store_ps(&x, _mm_sub_ps(_mm_load_ps(&x), _mm_set1_ps(s)));
    return *this;
}

gfx::vec3& gfx::vec3::operator=(float s) {
    _mm_store_ps(&x, _mm_set1_ps(s));
    return *this;
}

gfx::vec3 gfx::vec3::operator+(const vec3& a) const {
    vec3 b;
    _mm_store_ps(&b.x, _mm_add_ps(_mm_load_ps(&x), _mm_load_ps(&a.x)));
    return b;
}

gfx::vec3 gfx::vec3::add(const vec3 & a) const {
    vec3 b;
    _mm_store_ps(&b.x, _mm_add_ps(_mm_load_ps(&x), _mm_load_ps(&a.x)));
    return b;
}

gfx::vec3 gfx::vec3::operator-(const vec3 & a) const {
    vec3 b;
    _mm_store_ps(&b.x, _mm_sub_ps(_mm_load_ps(&x), _mm_load_ps(&a.x)));
    return b;
}

gfx::vec3 gfx::vec3::subtract(const vec3 & a) const {
    vec3 b;
    _mm_store_ps(&b.x, _mm_sub_ps(_mm_load_ps(&x), _mm_load_ps(&a.x)));
    return b;
}

gfx::vec3 gfx::vec3::operator*(float a) const {
    vec3 b;
    _mm_store_ps(&b.x, _mm_mul_ps(_mm_load_ps(&x), _mm_set1_ps(a)));
    return b;
}

gfx::vec3 gfx::vec3::negate(void) const {
    vec3 b;
    _mm_store_ps(&b.x, _mm_mul_ps(_mm_load_ps(&x), _mm_set1_ps(-1.f)));
    return b;
}

gfx::vec3 gfx::vec3::scale(float s) const {
    vec3 b;
    _mm_store_ps(&b.x, _mm_mul_ps(_mm_load_ps(&x), _mm_set1_ps(s)));
    return b;
}

gfx::vec3 gfx::vec3::multiply(float a) const {
    vec3 b;
    _mm_store_ps(&b.x, _mm_mul_ps(_mm_load_ps(&x), _mm_set1_ps(a)));
    return b;
}

gfx::vec3 gfx::vec3::operator*(const vec3 & a) const {
    vec3 b;
    _mm_store_ps(&b.x, _mm_mul_ps(_mm_load_ps(&x), _mm_load_ps(&a.x)));
    return b;
}

gfx::vec3 gfx::vec3::multiply(const vec3 & a) const {
    vec3 b;
    _mm_store_ps(&b.x, _mm_mul_ps(_mm_load_ps(&x), _mm_load_ps(&a.x)));
    return b;
}

float gfx::vec3::dot(const vec3 & a) {
    float res;
    __m128 r = _mm_mul_ps(_mm_setr_ps(x, y, z, 0.f),
                          _mm_setr_ps(a.x, a.y, a.z, 0.f));
    r = _mm_hadd_ps(r, r);
    r = _mm_hadd_ps(r, r);
    _mm_store_ss(&res, r);
    return res;
}

gfx::vec3 gfx::vec3::cross(const vec3 & a) {
    vec3 r;
    __m128 m0 = _mm_load_ps(&x);
    __m128 a0 = _mm_load_ps(&a.x);
    _mm_store_ps(&r.x,
        _mm_sub_ps(
            _mm_mul_ps(
                _mm_shuffle_ps(m0, m0, _MM_SHUFFLE(3, 0, 2, 1)),
                _mm_shuffle_ps(a0, a0, _MM_SHUFFLE(3, 1, 0, 2))),
            _mm_mul_ps(
                _mm_shuffle_ps(m0, m0, _MM_SHUFFLE(3, 1, 0, 2)),
                _mm_shuffle_ps(a0, a0, _MM_SHUFFLE(3, 0, 2, 1)))));
    r.w = 0.f;
    return r;
}

float gfx::vec3::angle(const vec3 & a) {
    float m, n, r;
    __m128 m0, n0, d0;

    // compute magnitude of this
    m0 = _mm_setr_ps(x, y, z, 0.f);
    m0 = _mm_mul_ps(m0, m0);
    m0 = _mm_hadd_ps(m0, m0);
    m0 = _mm_hadd_ps(m0, m0);
    m0 = _mm_sqrt_ps(m0);

    _mm_store_ss(&m, m0);

    // compute magnitude of a
    n0 = _mm_setr_ps(a.x, a.y, a.z, 0.f);
    n0 = _mm_mul_ps(n0, n0);
    n0 = _mm_hadd_ps(n0, n0);
    n0 = _mm_hadd_ps(n0, n0);
    n0 = _mm_sqrt_ps(n0);

    _mm_store_ss(&n, n0);

    // ensure no divide by 0
    if (!n || !m) {
        return 0.f;
    }

    // compute dot product of this and a
    d0 = _mm_mul_ps(_mm_setr_ps(x, y, z, 0.f), _mm_setr_ps(a.x, a.y, a.z, 0.f));
    d0 = _mm_hadd_ps(d0, d0);
    d0 = _mm_hadd_ps(d0, d0);
    _mm_store_ss(&r, d0);

    return acosf(r / (m * n));
}

float gfx::vec3::magnitude() const {
    float r;
    __m128 m0 = _mm_setr_ps(x, y, z, 0.f);

    m0 = _mm_mul_ps(m0, m0);
    m0 = _mm_hadd_ps(m0, m0);
    m0 = _mm_hadd_ps(m0, m0);
    m0 = _mm_sqrt_ps(m0);

    _mm_store_ss(&r, m0);
    return r;
}

gfx::vec3& gfx::vec3::normalize() {
    float r;
    __m128 m0 = _mm_setr_ps(x, y, z, 0.f);

    __m128 m1 = _mm_mul_ps(m0, m0);
    m1 = _mm_hadd_ps(m1, m1);
    m1 = _mm_hadd_ps(m1, m1);
    m1 = _mm_sqrt_ps(m1);

    _mm_store_ss(&r, m1);

    if (!r) {
        return *this;
    }

    _mm_store_ps(&x, _mm_div_ps(m0, m1));
    return *this;
}

gfx::vec3 gfx::vec3::normalized() const {
    float r;
    vec3 vr(0.f, 0.f, 0.f);
    __m128 m0 = _mm_setr_ps(x, y, z, 0.f);

    __m128 m1 = _mm_mul_ps(m0, m0);
    m1 = _mm_hadd_ps(m1, m1);
    m1 = _mm_hadd_ps(m1, m1);
    m1 = _mm_sqrt_ps(m1);

    _mm_store_ss(&r, m1);

    if (!r) {
        return vr;
    }

    _mm_store_ps(&vr.x, _mm_div_ps(m0, m1));
    return vr;
}


