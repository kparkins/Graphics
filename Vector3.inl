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
    _mm_store_ps(&x, _mm_mul_ps(_mm_load_ps(&x), _mm_load_ps(&a.x)));
    return *this;
}

Vector3& Vector3::operator+=(const Vector3 & a) {
    _mm_store_ps(&x, _mm_add_ps(_mm_load_ps(&x), _mm_load_ps(&a.x)));
    return *this;
}

Vector3& Vector3::operator-=(const Vector3 & a) {
    _mm_store_ps(&x, _mm_sub_ps(_mm_load_ps(&x), _mm_load_ps(&a.x)));
    return *this;
}

Vector3& Vector3::operator=(const Vector3 & a) {
    _mm_store_ps(&x, _mm_load_ps(&a.x));
    return *this;
}

Vector3& Vector3::operator*=(float s) {
    _mm_store_ps(&x, _mm_mul_ps(_mm_load_ps(&x), _mm_set1_ps(s)));
    return *this;
}

Vector3& Vector3::operator+=(float s) {
    _mm_store_ps(&x, _mm_add_ps(_mm_load_ps(&x), _mm_set1_ps(s)));
    return *this;
}

Vector3& Vector3::operator-=(float s) {
    _mm_store_ps(&x, _mm_sub_ps(_mm_load_ps(&x), _mm_set1_ps(s)));
    return *this;
}

Vector3& Vector3::operator=(float s) {
    _mm_store_ps(&x, _mm_set1_ps(s));
    return *this;
}

Vector3 Vector3::operator+(const Vector3& a) const {
    Vector3 b;
    _mm_store_ps(&b.x, _mm_add_ps(_mm_load_ps(&x), _mm_load_ps(&a.x)));
    return b;
}

Vector3 Vector3::add(const Vector3 & a) const {
    Vector3 b;
    _mm_store_ps(&b.x, _mm_add_ps(_mm_load_ps(&x), _mm_load_ps(&a.x)));
    return b;
}

Vector3 Vector3::operator-(const Vector3 & a) const {
    Vector3 b;
    _mm_store_ps(&b.x, _mm_sub_ps(_mm_load_ps(&x), _mm_load_ps(&a.x)));
    return b;
}

Vector3 Vector3::subtract(const Vector3 & a) const {
    Vector3 b;
    _mm_store_ps(&b.x, _mm_sub_ps(_mm_load_ps(&x), _mm_load_ps(&a.x)));
    return b;
}

Vector3 Vector3::operator*(float a) const {
    Vector3 b;
    _mm_store_ps(&b.x, _mm_mul_ps(_mm_load_ps(&x), _mm_set1_ps(a)));
    return b;
}

Vector3 Vector3::negate(void) const {
    Vector3 b;
    _mm_store_ps(&b.x, _mm_mul_ps(_mm_load_ps(&x), _mm_set1_ps(-1.f)));
    return b;
}

Vector3 Vector3::scale(float s) const {
    Vector3 b;
    _mm_store_ps(&b.x, _mm_mul_ps(_mm_load_ps(&x), _mm_set1_ps(s)));
    return b;
}

Vector3 Vector3::multiply(float a) const {
    Vector3 b;
    _mm_store_ps(&b.x, _mm_mul_ps(_mm_load_ps(&x), _mm_set1_ps(a)));
    return b;
}

Vector3 Vector3::operator*(const Vector3 & a) const {
    Vector3 b;
    _mm_store_ps(&b.x, _mm_mul_ps(_mm_load_ps(&x), _mm_load_ps(&a.x)));
    return b;
}

Vector3 Vector3::multiply(const Vector3 & a) const {
    Vector3 b;
    _mm_store_ps(&b.x, _mm_mul_ps(_mm_load_ps(&x), _mm_load_ps(&a.x)));
    return b;
}

float Vector3::dot(const Vector3 & a) {
    float res;
    __m128 r = _mm_mul_ps(_mm_setr_ps(x, y, z, 0.f),
                          _mm_setr_ps(a.x, a.y, a.z, 0.f));
    r = _mm_hadd_ps(r, r);
    r = _mm_hadd_ps(r, r);
    _mm_store_ss(&res, r);
    return res;
}

/*  xr = y * a.z - z * a.y
 *  yr = z * a.x - x * a.z
 *  zr = x * a.y - y * a.x
 */
Vector3 Vector3::cross(const Vector3 & a) {
    Vector3 r;
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

float Vector3::angle(const Vector3 & a) {
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

float Vector3::magnitude(void) const {
    float r;
    __m128 m0 = _mm_setr_ps(x, y, z, 0.f);

    m0 = _mm_mul_ps(m0, m0);
    m0 = _mm_hadd_ps(m0, m0);
    m0 = _mm_hadd_ps(m0, m0);
    m0 = _mm_sqrt_ps(m0);

    _mm_store_ss(&r, m0);
    return r;
}

Vector3 Vector3::normalize(void) const {
    float r;
    Vector3 vr(0.f, 0.f, 0.f);
    __m128 m0 = _mm_setr_ps(x, y, z, 0.f);

    m0 = _mm_mul_ps(m0, m0);
    m0 = _mm_hadd_ps(m0, m0);
    m0 = _mm_hadd_ps(m0, m0);
    m0 = _mm_sqrt_ps(m0);

    _mm_store_ss(&r, m0);

    if (!r) {
        return vr;
    }

    _mm_store_ps(&vr.x, _mm_div_ps(_mm_setr_ps(x, y, z, 0.f), m0));
    return vr;
}
