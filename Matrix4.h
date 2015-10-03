#ifndef MATRIX4_H
#define MATRIX4_H

#include <cassert>
#include <string>
#include "immintrin.h"
#include <math.h>
#include <iostream>
#include <iomanip>
#include <cstring>

class Vector3;
class Vector4;

class Matrix4 {

public:
    
    Matrix4();
    Matrix4(float, float, float, float,
            float, float, float, float,
            float, float, float, float,
            float, float, float, float);
    
    inline void set(float, float, float, float,
                    float, float, float, float,
                    float, float, float, float,
                    float, float, float, float);
    
    inline float get(int,int);
    
    inline Matrix4& operator=(const Matrix4 &);
    
    inline float* operator[](int);
    
    inline float* ptr();
    
    inline void identity();
    
    inline Matrix4 multiply(const Matrix4 &);
    inline Matrix4 operator*(const Matrix4 &);
    Vector4 multiply(Vector4 &);
    Vector4 operator*(Vector4 &);
    Vector3 multiply(Vector3 &);
    Vector3 operator*(Vector3 &);
    
    inline Matrix4& makeRotateX(float);
    inline Matrix4& makeRotateY(float);
    inline Matrix4& makeRotateZ(float);
    Matrix4& makeRotateArbitrary(const Vector3 &, float);
    
    inline Matrix4& makeScale(float, float, float);
    inline Matrix4& makeScale(float);
    
    inline Matrix4& makeTranslate(float, float, float);
    Matrix4& makeTranslate(const Vector3 &);
    
    Matrix4 transpose(void);
    Matrix4 inverse(void);
    Matrix4 rigidInverse(void);
    
    Matrix4 makePerspectiveProjection(float, float, float, float, float);
    Matrix4 makeViewport(float, float, float, float);
    
    inline void print(const std::string &);
    
protected:
    
    __attribute__ ((aligned(16))) float m[4][4];
    
};

#include "Matrix4.inl"
#endif
