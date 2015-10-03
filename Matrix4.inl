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

void Matrix4::identity() {
    static const float ident[4][4] = {
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    };
    memcpy(static_cast<void*>(&m), ident, sizeof(m));
}

Matrix4 Matrix4::operator*(const Matrix4 & a) {
    Matrix4 b;
    
    /*for (int row = 0; row < 4; ++row) {
     for (int col = 0; col < 4; ++col) {
     b[col][row] = m[0][row] * a[col][0] +
     m[1][row] * a[col][1] +
     m[2][row] * a[col][2] +
     m[3][row] * a[col][3];
     }
     } */
    __m128 m0c = _mm_load_ps(m[0]);
    __m128 m1c = _mm_load_ps(m[1]);
    __m128 m2c = _mm_load_ps(m[2]);
    __m128 m3c = _mm_load_ps(m[3]);
    
    
    __m128 a0v = _mm_set1_ps(a.m[0][0]);
    __m128 a1v = _mm_set1_ps(a.m[0][1]);
    __m128 a2v = _mm_set1_ps(a.m[0][2]);
    __m128 a3v = _mm_set1_ps(a.m[0][3]);
    
    __m128 r0 = _mm_add_ps(_mm_add_ps(_mm_mul_ps(m0c, a0v), _mm_mul_ps(m1c, a1v)),
                           _mm_add_ps(_mm_mul_ps(m2c, a2v), _mm_mul_ps(m3c, a3v)));
    
    _mm_store_ps(&b[0][0], r0);
    
    a0v = _mm_set1_ps(a.m[1][0]);
    a1v = _mm_set1_ps(a.m[1][1]);
    a2v = _mm_set1_ps(a.m[1][2]);
    a3v = _mm_set1_ps(a.m[1][3]);
    
    __m128 r1 = _mm_add_ps(_mm_add_ps(_mm_mul_ps(m0c, a0v), _mm_mul_ps(m1c, a1v)),
                           _mm_add_ps(_mm_mul_ps(m2c, a2v), _mm_mul_ps(m3c, a3v)));
    
    _mm_store_ps(&b[1][0], r1);
    
    a0v = _mm_set1_ps(a.m[2][0]);
    a1v = _mm_set1_ps(a.m[2][1]);
    a2v = _mm_set1_ps(a.m[2][2]);
    a3v = _mm_set1_ps(a.m[2][3]);
    
    __m128 r2 = _mm_add_ps(_mm_add_ps(_mm_mul_ps(m0c, a0v), _mm_mul_ps(m1c, a1v)),
                           _mm_add_ps(_mm_mul_ps(m2c, a2v), _mm_mul_ps(m3c, a3v)));
    
    _mm_store_ps(&b[2][0], r2);
    
    a0v = _mm_set1_ps(a.m[3][0]);
    a1v = _mm_set1_ps(a.m[3][1]);
    a2v = _mm_set1_ps(a.m[3][2]);
    a3v = _mm_set1_ps(a.m[3][3]);
    
    __m128 r3 = _mm_add_ps(_mm_add_ps(_mm_mul_ps(m0c, a0v), _mm_mul_ps(m1c, a1v)),
                           _mm_add_ps(_mm_mul_ps(m2c, a2v), _mm_mul_ps(m3c, a3v)));
    
    _mm_store_ps(&b[3][0], r3);
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
    
    //Configure this matrix to be a rotation about the Z-Axis by 'angle' radians
    m[0][0] = cos(angle);
    m[0][1] = sin(angle);
    m[1][0] = -sin(angle);
    m[1][1] = cos(angle);
    
    return *this;
}

Matrix4& Matrix4::makeScale(float sx, float sy, float sz) {
    this->identity();
    
    //Configure this matrix to be a sclaing by sx, sy, sz
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
    
    //Configure this matrix to be a translation by vector 'a'
    m[3][0] = x;
    m[3][1] = y;
    m[3][2] = z;
    
    return *this;
}

void Matrix4::print(const std::string & comment) {
    //Width constants and variables
    static const int pointWidth = 1;
    static const int precisionWidth = 4;
    int integerWidth = 1;
    
    //Determine the necessary width to the left of the decimal point
    float* elementPtr = (float*)m;
    float maxValue = fabsf(*(elementPtr++));
    while(elementPtr++ < ((float*)m+16)) if(fabsf(*elementPtr) > maxValue) maxValue = fabsf(*elementPtr);
    while(maxValue >= 10.0) { ++integerWidth; maxValue /= 10.0; }
    
    //Sum up the widths to determine the cell width needed
    int cellWidth = integerWidth + pointWidth + precisionWidth;
    
    //Set the stream parameters for fixed number of digits after the decimal point
    //and a set number of precision digits
    std::cout << std::fixed;
    std::cout << std::setprecision(precisionWidth);
    
    //Print the comment
    std::cout << comment << std::endl;
    
    //Loop through the matrix elements, format each, and print them to screen
    float cellValue;
    for(int element = 0; element < 4; element++) {
        std::cout << std::setw(1) << (element == 0 ? "[" : " ");
        for(int vector = 0; vector < 4; vector++) {
            cellValue =  m[vector][element];
            std::cout << std::setw(cellWidth + (cellValue >= 0.0 ? 1 : 0)) << cellValue;
            std::cout << std::setw(0) << (vector < 3 ? " " : "");
        }
        std::cout << std::setw(1) << (element == 3 ? "]" : " ") << std::endl;
    }
}
