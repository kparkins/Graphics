#include "Matrix4.h"

void Matrix4::set(float m00, float m01, float m02, float m03,
                  float m10, float m11, float m12, float m13,
                  float m20, float m21, float m22, float m23,
                  float m30, float m31, float m32, float m33) {
    m[0][0] = m00;
    m[0][1] = m01;
    m[0][2] = m02;
    m[0][3] = m03;
    m[1][0] = m10;
    m[1][1] = m11;
    m[1][2] = m12;
    m[1][3] = m13;
    m[2][0] = m20;
    m[2][1] = m21;
    m[2][2] = m22;
    m[2][3] = m23;
    m[3][0] = m30;
    m[3][1] = m31;
    m[3][2] = m32;
    m[3][3] = m33;
}

float Matrix4::get(int column, int element) {
    return m[column][element];
}

Matrix4& Matrix4::operator=(const Matrix4 & a) {
    memcpy(static_cast<void*>(&m), static_cast<const void*>(&a), sizeof(m));
    return *this;
}

float* Matrix4::operator[](int i) {
    return m[i];
}

float* Matrix4::ptr() {
    return &m[0][0];
}

Matrix4& Matrix4::identity() {
    static const float ident[4][4] = {
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    };
    memcpy(static_cast<void*>(&m), ident, sizeof(m));
    return *this;
}

Matrix4 Matrix4::operator*(const Matrix4 & a) {
    Matrix4 b;
    __m128 m0c = _mm_load_ps(m[0]);
    __m128 m1c = _mm_load_ps(m[1]);
    __m128 m2c = _mm_load_ps(m[2]);
    __m128 m3c = _mm_load_ps(m[3]);
    __m128 a0v = _mm_set1_ps(a.m[0][0]);
    __m128 a1v = _mm_set1_ps(a.m[0][1]);
    __m128 a2v = _mm_set1_ps(a.m[0][2]);
    __m128 a3v = _mm_set1_ps(a.m[0][3]);
   
    _mm_store_ps(&b[0][0], 
        _mm_add_ps(
            _mm_add_ps(
                _mm_mul_ps(m0c, a0v), 
                _mm_mul_ps(m1c, a1v)),
            _mm_add_ps(
                _mm_mul_ps(m2c, a2v), 
                _mm_mul_ps(m3c, a3v))));
    
    a0v = _mm_set1_ps(a.m[1][0]);
    a1v = _mm_set1_ps(a.m[1][1]);
    a2v = _mm_set1_ps(a.m[1][2]);
    a3v = _mm_set1_ps(a.m[1][3]);
    
    _mm_store_ps(&b[1][0], 
        _mm_add_ps(
            _mm_add_ps(
                _mm_mul_ps(m0c, a0v), 
                _mm_mul_ps(m1c, a1v)),
            _mm_add_ps(
                _mm_mul_ps(m2c, a2v), 
                _mm_mul_ps(m3c, a3v))));
    
    a0v = _mm_set1_ps(a.m[2][0]);
    a1v = _mm_set1_ps(a.m[2][1]);
    a2v = _mm_set1_ps(a.m[2][2]);
    a3v = _mm_set1_ps(a.m[2][3]);

    _mm_store_ps(&b[2][0], 
        _mm_add_ps(
            _mm_add_ps(
                _mm_mul_ps(m0c, a0v), 
                _mm_mul_ps(m1c, a1v)),
            _mm_add_ps(
                _mm_mul_ps(m2c, a2v), 
                _mm_mul_ps(m3c, a3v))));
    
    a0v = _mm_set1_ps(a.m[3][0]);
    a1v = _mm_set1_ps(a.m[3][1]);
    a2v = _mm_set1_ps(a.m[3][2]);
    a3v = _mm_set1_ps(a.m[3][3]);
    
    _mm_store_ps(&b[3][0], 
        _mm_add_ps(
            _mm_add_ps(
                _mm_mul_ps(m0c, a0v), 
                _mm_mul_ps(m1c, a1v)),
            _mm_add_ps(
                _mm_mul_ps(m2c, a2v),
                _mm_mul_ps(m3c, a3v))));
    return b;
}


Matrix4 Matrix4::multiply(const Matrix4 & a) {
    return (*this) * a;
}

Matrix4& Matrix4::makeRotateX(float angle) {
    this->identity();
    
    m[1][1] = cos(angle);
    m[1][2] = sin(angle);
    m[2][1] = -sin(angle);
    m[2][2] = cos(angle);
    
    return *this;
}

Matrix4& Matrix4::makeRotateY(float angle) {
    this->identity();
    
    m[0][0] = cos(angle);
    m[0][2] = -sin(angle);
    m[2][0] = sin(angle);
    m[2][2] = cos(angle);
    
    return *this;
}

Matrix4& Matrix4::makeRotateZ(float angle) {
    this->identity();

    m[0][0] = cos(angle);
    m[0][1] = sin(angle);
    m[1][0] = -sin(angle);
    m[1][1] = cos(angle);
    
    return *this;
}

Matrix4& Matrix4::makeScale(float sx, float sy, float sz) {
    this->identity();

    m[0][0] *= sx;
    m[1][1] *= sy;
    m[2][2] *= sz;

    return *this;
}

Matrix4& Matrix4::makeScale(float s) {
    return makeScale(s, s, s);
}


Matrix4& Matrix4::makeTranslate(float x, float y, float z) {
    this->identity();

    m[3][0] = x;
    m[3][1] = y;
    m[3][2] = z;
    return *this;
}
