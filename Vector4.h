#ifndef VECTOR4_H
#define VECTOR4_H

#include <string>
#include <math.h>
#include <iostream>
#include <cstring>

class Vector3;

class Vector4 {
    
public:
    
    Vector4();
    Vector4(float, float, float);
    Vector4(float, float, float, float);
    
    inline float& x();
    inline float& y();
    inline float& z();
    inline float& w();
    inline float* ptr();
    inline float& operator[](int);
    
    inline void set(float,float,float,float);
    
    
    inline Vector4 add(Vector4&);
    inline Vector4 operator+(Vector4);
    
    inline Vector4 subtract(Vector4&);
    inline Vector4 operator-(Vector4);
    
    inline Vector4 dehomogenize();
    
    Vector3 toVector3();
    
    inline float dot(Vector4);
    
    inline void print(std::string);
    
protected:
    
    __attribute__ ((aligned(16))) float m[4];

};

#include "Vector4.inl"
#endif
