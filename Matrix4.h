#ifndef MATRIX4_H
#define MATRIX4_H

#include <string>
#include <math.h>
#include <cassert>
#include <iomanip>
#include <cstring>
#include <iostream>

#include "immintrin.h"
#include "Macros.h"

class Vector3;
class Vector4;

class Matrix4 {

public:
    
    Matrix4();
    Matrix4(float, float, float, float,
            float, float, float, float,
            float, float, float, float,
            float, float, float, float);
    
    FORCE_INLINE void set(float, float, float, float,
                          float, float, float, float,
                          float, float, float, float,
                          float, float, float, float);
    
    FORCE_INLINE float get(int,int);
    
    FORCE_INLINE Matrix4& operator=(const Matrix4 &);
    
    FORCE_INLINE float* operator[](int);
    
    FORCE_INLINE float* ptr();
    
    FORCE_INLINE Matrix4& identity();
    
    FORCE_INLINE Matrix4 multiply(const Matrix4 &);
    FORCE_INLINE Matrix4 operator*(const Matrix4 &);
    
    Vector4 multiply(Vector4 &);
    Vector4 operator*(Vector4 &);
    Vector3 multiply(Vector3 &);
    Vector3 operator*(Vector3 &);
    
    FORCE_INLINE Matrix4& makeRotateX(float);
    FORCE_INLINE Matrix4& makeRotateY(float);
    FORCE_INLINE Matrix4& makeRotateZ(float);
    Matrix4& makeRotateArbitrary(const Vector3 &, float);
    
    FORCE_INLINE Matrix4& makeScale(float, float, float);
    FORCE_INLINE Matrix4& makeScale(float);
    
    FORCE_INLINE Matrix4& makeTranslate(float, float, float);
    Matrix4& makeTranslate(const Vector3 &);
    
    Matrix4 transpose(void);
    Matrix4 inverse(void);
    Matrix4 rigidInverse(void);
    
    Matrix4& makePerspectiveProjection(float, float, float, float, float);
    Matrix4& makeViewport(float, float, float, float);
    
    void print(const std::string &);
    
    ALIGN_16 float m[4][4];
    
};

#include "Matrix4.inl"
#endif
