#include "Matrix4.h"
#include "Vector4.h"
#include "Vector3.h"

Matrix4::Matrix4() {
    std::memset(static_cast<void*>(&m), 0, sizeof(float) * 16);
}

Matrix4::Matrix4(float m00, float m01, float m02, float m03,
                 float m10, float m11, float m12, float m13,
                 float m20, float m21, float m22, float m23,
                 float m30, float m31, float m32, float m33 ) {
    this->set(m00, m01, m02, m03,
              m10, m11, m12, m13,
              m20, m21, m22, m23,
              m30, m31, m32, m33);
}

/*float* bptr = b.ptr();
 for(int i = 0; i < 4; ++i) {
 *bptr++ = m[0][i] * a[0] + m[1][i] * a[1] + m[2][i] * a[2] + m[3][i] * a[3];
 }*/
Vector4 Matrix4::operator*(Vector4 & a) {
    Vector4 b(0.f, 0.f, 0.f, 0.f);
 
    __m128 m0c = _mm_load_ps(m[0]);
    __m128 m1c = _mm_load_ps(m[1]);
    __m128 m2c = _mm_load_ps(m[2]);
    __m128 m3c = _mm_load_ps(m[3]);
    __m128 a0v = _mm_set1_ps(a.x);
    __m128 a1v = _mm_set1_ps(a.y);
    __m128 a2v = _mm_set1_ps(a.z);
    __m128 a3v = _mm_set1_ps(a.w);
    
    __m128 result = _mm_add_ps(_mm_add_ps(_mm_mul_ps(m0c, a0v), _mm_mul_ps(m1c, a1v)),
                               _mm_add_ps(_mm_mul_ps(m2c, a2v), _mm_mul_ps(m3c, a3v)));
    _mm_store_ps(b.ptr(), result);
    
    return b;
}

Vector4 Matrix4::multiply(Vector4 & a) {
    return (*this) * a;
}

/* float* bptr = b.ptr();
 for(int i = 0; i < 3; ++i) {
 *bptr++ = m[0][i] * a[0] + m[1][i] * a[1] + m[2][i] * a[2];
 }*/

Vector3 Matrix4::operator*(Vector3 & a) {
    Vector3 b(0.f, 0.f, 0.f);

    __m128 m0c = _mm_load_ps(m[0]);
    __m128 m1c = _mm_load_ps(m[1]);
    __m128 m2c = _mm_load_ps(m[2]);
    __m128 a0v = _mm_set1_ps(a.x);
    __m128 a1v = _mm_set1_ps(a.y);
    __m128 a2v = _mm_set1_ps(a.z);
    
    __m128 result = _mm_add_ps(_mm_add_ps(_mm_mul_ps(m0c, a0v), _mm_mul_ps(m1c, a1v)),
                               _mm_mul_ps(m2c, a2v));
    _mm_store_ps(&b.x, result);
    return b;
}

Vector3 Matrix4::multiply(Vector3 & a) {
    return (*this) * a;
}

Matrix4& Matrix4::makeRotateArbitrary(const Vector3 & a, float angle) {
    this->identity();
    Vector3 b = a.normalize();
    
    float cos0 = cos(angle);
    float sin0 = sin(angle);
    float omcos0 = 1 - cos0;
    float ux = b.x;
    float uy = b.y;
    float uz = b.z;
    float uzsin0 = uz * sin0;
    float uxsin0 = ux * sin0;
    float uysin0 = uy * sin0;
    
    m[0][0] = cos0 + ux * ux * omcos0;
    m[0][1] = uy * ux * omcos0 + uzsin0;
    m[0][2] = uz * ux * omcos0 - uysin0;
    
    m[1][0] = ux * uy * omcos0 - uzsin0;
    m[1][1] = cos0 + uy * uy * omcos0;
    m[1][2] = uz * uy * omcos0 + uxsin0;
    
    m[2][0] = ux * uz * omcos0 + uysin0;
    m[2][1] = uy * uz * omcos0 - uxsin0;
    m[2][2] = cos0 + uz * uz * omcos0;
    
    return *this;
}

Matrix4& Matrix4::makeTranslate(const Vector3 & a) {
    return this->makeTranslate(a.x, a.y, a.z);
}

Matrix4 Matrix4::transpose(void) {
    Matrix4 b;
    for(int x = 0; x < 4; ++x) {
        for(int y = 0; y < 4; ++y) {
            b.m[y][x] = m[x][y];
        }
    }
    return b;
}

//Hint: Try basing this on code by cool people on the internet
//In this class it is okay to use code from the internet
//So long as you fully understand the code and can clearly explain it if asked to
//http://stackoverflow.com/questions/2624422/efficient-4x4-matrix-inverse-affine-transform
Matrix4 Matrix4::inverse(void) {
    Matrix4 b;
    
    //Not required
    //Calculate the inverse of this matrix
    
    return b;
}

Matrix4 Matrix4::rigidInverse(void) {
    Matrix4 b;
    
    //Project 2
    //Calculate the inverse of this matrix with the assumption that it is a rigid transformation
    //This will be useful when implementing cameras!
    
    return b;
}


Matrix4 Matrix4::makePerspectiveProjection(float fov, float width, float height, float near, float far) {
    identity();
    
    //Project 3
    //Make this matrix a perspectice project matrix using fov, width, height, near and far
    //See the lecture slides for details
    
    return *this;
}

Matrix4 Matrix4::makeViewport(float xmin, float xmax, float ymin, float ymax) {
    identity();
    
    //Project 3
    //Make this matrix a viewport matrix using xmin, xmax, ymin, and ymax
    //See the lecture slides for details
    
    return *this;
}
