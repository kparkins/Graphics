#include "Matrix4.h"

void Matrix4::set(float m00, float m01, float m02, float m03,
                  float m10, float m11, float m12, float m13,
                  float m20, float m21, float m22, float m23,
                  float m30, float m31, float m32, float m33) {
    m_matrix[0][0] = m00;
    m_matrix[0][1] = m01;
    m_matrix[0][2] = m02;
    m_matrix[0][3] = m03;
    m_matrix[1][0] = m10;
    m_matrix[1][1] = m11;
    m_matrix[1][2] = m12;
    m_matrix[1][3] = m13;
    m_matrix[2][0] = m20;
    m_matrix[2][1] = m21;
    m_matrix[2][2] = m22;
    m_matrix[2][3] = m23;
    m_matrix[3][0] = m30;
    m_matrix[3][1] = m31;
    m_matrix[3][2] = m32;
    m_matrix[3][3] = m33;
}

float Matrix4::get(int column, int element) {
    return m_matrix[column][element];
}

Matrix4& Matrix4::operator=(const Matrix4 & a) {
    memcpy(static_cast<void*>(&m_matrix), static_cast<const void*>(&a), sizeof(m_matrix));
    return *this;
}

float* Matrix4::operator[](int i) {
    return m_matrix[i];
}

float* Matrix4::ptr() {
    return &m_matrix[0][0];
}

void Matrix4::identity() {
    static const float ident[4][4] = {
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    };
    memcpy(static_cast<void*>(&m_matrix), ident, sizeof(m_matrix));
}

Matrix4 Matrix4::operator*(const Matrix4 & a) {
    Matrix4 b;
    __m128 m0c = _mm_load_ps(m_matrix[0]);
    __m128 m1c = _mm_load_ps(m_matrix[1]);
    __m128 m2c = _mm_load_ps(m_matrix[2]);
    __m128 m3c = _mm_load_ps(m_matrix[3]);
    __m128 a0v = _mm_set1_ps(a.m_matrix[0][0]);
    __m128 a1v = _mm_set1_ps(a.m_matrix[0][1]);
    __m128 a2v = _mm_set1_ps(a.m_matrix[0][2]);
    __m128 a3v = _mm_set1_ps(a.m_matrix[0][3]);
   
    _mm_store_ps(&b[0][0], 
        _mm_add_ps(
            _mm_add_ps(
                _mm_mul_ps(m0c, a0v), 
                _mm_mul_ps(m1c, a1v)),
            _mm_add_ps(
                _mm_mul_ps(m2c, a2v), 
                _mm_mul_ps(m3c, a3v))));
    
    a0v = _mm_set1_ps(a.m_matrix[1][0]);
    a1v = _mm_set1_ps(a.m_matrix[1][1]);
    a2v = _mm_set1_ps(a.m_matrix[1][2]);
    a3v = _mm_set1_ps(a.m_matrix[1][3]);
    
    _mm_store_ps(&b[1][0], 
        _mm_add_ps(
            _mm_add_ps(
                _mm_mul_ps(m0c, a0v), 
                _mm_mul_ps(m1c, a1v)),
            _mm_add_ps(
                _mm_mul_ps(m2c, a2v), 
                _mm_mul_ps(m3c, a3v))));
    
    a0v = _mm_set1_ps(a.m_matrix[2][0]);
    a1v = _mm_set1_ps(a.m_matrix[2][1]);
    a2v = _mm_set1_ps(a.m_matrix[2][2]);
    a3v = _mm_set1_ps(a.m_matrix[2][3]);

    _mm_store_ps(&b[2][0], 
        _mm_add_ps(
            _mm_add_ps(
                _mm_mul_ps(m0c, a0v), 
                _mm_mul_ps(m1c, a1v)),
            _mm_add_ps(
                _mm_mul_ps(m2c, a2v), 
                _mm_mul_ps(m3c, a3v))));
    
    a0v = _mm_set1_ps(a.m_matrix[3][0]);
    a1v = _mm_set1_ps(a.m_matrix[3][1]);
    a2v = _mm_set1_ps(a.m_matrix[3][2]);
    a3v = _mm_set1_ps(a.m_matrix[3][3]);
    
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
    
    m_matrix[1][1] = cos(angle);
    m_matrix[1][2] = sin(angle);
    m_matrix[2][1] = -sin(angle);
    m_matrix[2][2] = cos(angle);
    
    return *this;
}

Matrix4& Matrix4::makeRotateY(float angle) {
    this->identity();
    
    m_matrix[0][0] = cos(angle);
    m_matrix[0][2] = -sin(angle);
    m_matrix[2][0] = sin(angle);
    m_matrix[2][2] = cos(angle);
    
    return *this;
}

Matrix4& Matrix4::makeRotateZ(float angle) {
    this->identity();

    m_matrix[0][0] = cos(angle);
    m_matrix[0][1] = sin(angle);
    m_matrix[1][0] = -sin(angle);
    m_matrix[1][1] = cos(angle);
    
    return *this;
}

Matrix4& Matrix4::makeScale(float sx, float sy, float sz) {
    this->identity();

    m_matrix[0][0] *= sx;
    m_matrix[1][1] *= sy;
    m_matrix[2][2] *= sz;

    return *this;
}

Matrix4& Matrix4::makeScale(float s) {
    return makeScale(s, s, s);
}


Matrix4& Matrix4::makeTranslate(float x, float y, float z) {
    this->identity();

    m_matrix[3][0] = x;
    m_matrix[3][1] = y;
    m_matrix[3][2] = z;
    return *this;
}
