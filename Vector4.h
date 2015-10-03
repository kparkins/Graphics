#ifndef VECTOR4_H
#define VECTOR4_H

#include <string>
#include <math.h>
#include <iostream>
#include <cstring>
#include "immintrin.h"

class Vector3;

class Vector4 {
    
public:
    
    Vector4();
    Vector4(float, float, float);
    Vector4(float, float, float, float);
    
    inline void set(float,float,float,float);
    
    inline float* ptr();
    inline float& operator[](int);
    
    inline Vector4 add(const Vector4 &) const;
    inline Vector4 operator+(const Vector4 &) const;
    
    inline Vector4 subtract(const Vector4 &) const;
    inline Vector4 operator-(const Vector4 &) const;
    
    inline Vector4 dehomogenize() const;
    
    Vector3 toVector3();
    
    inline float dot(const Vector4 &) const;
    
    inline void print(const std::string &) const;
    
    struct {
        float x,y,z,w;
    } __attribute__ ((aligned(16)));

};

#include "Vector4.inl"
#endif
