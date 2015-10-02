#ifndef VECTOR3_H
#define VECTOR3_H

#include <string>
#include <math.h>
#include <iostream>
#include <cstring>
#include "Vector4.h"

class Vector4;

class Vector3 {

public:
    
    Vector3();
    Vector3(float, float, float);
    virtual ~Vector3(void);
    
    inline void set(float, float, float);
    inline void set(int index, float value);
    
    inline float& x();
    inline float& y();
    inline float& z();
    
    inline float& operator[](int);
    inline float* ptr();
    
    inline Vector3 add(Vector3);
    inline Vector3 operator+(Vector3);
    
    inline Vector3 subtract(Vector3);
    inline Vector3 operator-(Vector3);
    
    inline Vector3 negate(void);
    inline Vector3 scale(float);
    inline Vector3 multiply(float);
    inline Vector3 operator*(float);
    inline Vector3 multiply(Vector3);
    inline Vector3 operator*(Vector3);
    
    inline float dot(Vector3);
    inline Vector3 cross(Vector3);
    
    inline float angle(Vector3);
    
    inline float magnitude(void);
    
    inline Vector3 normalize(void);
    
    Vector4 toVector4(float);
    
    inline void print(std::string);


protected:
    
    __attribute__ ((aligned(16))) float m[4];
    
};

#include "Vector3.inl"
#endif
