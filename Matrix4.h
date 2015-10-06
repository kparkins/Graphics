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
    
    force_inline void set(float, float, float, float,
                          float, float, float, float,
                          float, float, float, float,
                          float, float, float, float);
    
    force_inline float get(int,int);
    
    force_inline Matrix4& operator=(const Matrix4 &);
    
    force_inline float* operator[](int);
    
    force_inline float* ptr();
    
    force_inline void identity();
    
    force_inline Matrix4 multiply(const Matrix4 &);
    force_inline Matrix4 operator*(const Matrix4 &);
    
    Vector4 multiply(Vector4 &);
    Vector4 operator*(Vector4 &);
    Vector3 multiply(Vector3 &);
    Vector3 operator*(Vector3 &);
    
    force_inline Matrix4& makeRotateX(float);
    force_inline Matrix4& makeRotateY(float);
    force_inline Matrix4& makeRotateZ(float);
    Matrix4& makeRotateArbitrary(const Vector3 &, float);
    
    force_inline Matrix4& makeScale(float, float, float);
    force_inline Matrix4& makeScale(float);
    
    force_inline Matrix4& makeTranslate(float, float, float);
    Matrix4& makeTranslate(const Vector3 &);
    
    Matrix4 transpose(void);
    Matrix4 inverse(void);
    Matrix4 rigidInverse(void);
    
    Matrix4 makePerspectiveProjection(float, float, float, float, float);
    Matrix4 makeViewport(float, float, float, float);
    
    void print(const std::string &);
    
    align_16 float m[4][4];
    
};

#include "Matrix4.inl"
#endif
