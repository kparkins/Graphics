#ifndef VECTOR3_H
#define VECTOR3_H

#include <string>
#include <math.h>
#include <iostream>
#include "immintrin.h"
#include <cstring>
#include "Vector4.h"

class Vector4;

class Vector3 {

public:
    
    Vector3();
    Vector3(float, float, float);
    virtual ~Vector3(void);
    
    inline void set(float, float, float);

    inline float* ptr();
    inline const float* const_ptr();
    inline float& operator[](int);
    
    inline Vector3& operator*=(const Vector3&);
    inline Vector3& operator+=(const Vector3&);
    inline Vector3& operator-=(const Vector3&);
    inline Vector3& operator=(const Vector3&);
    
    inline Vector3& operator*=(float);
    inline Vector3& operator+=(float);
    inline Vector3& operator-=(float);
    inline Vector3& operator=(float);
    
    inline Vector3 add(const Vector3 &) const;
    inline Vector3 operator+(const Vector3 &) const;
    
    inline Vector3 subtract(const Vector3 &) const;
    inline Vector3 operator-(const Vector3 &) const;
    
    inline Vector3 negate(void) const;
    inline Vector3 scale(float) const;
    inline Vector3 multiply(float) const;
    inline Vector3 operator*(float) const;
    inline Vector3 multiply(const Vector3 &) const;
    inline Vector3 operator*(const Vector3 &) const;
    
    inline float dot(const Vector3 &) const;
    inline Vector3 cross(const Vector3 &) const;
    
    inline float angle(const Vector3 &) const;
    
    inline float magnitude(void) const;
    
    inline Vector3 normalize(void) const;
    
    Vector4 toVector4(float) const;
    
    inline void print(const std::string &)  const;

    struct {
        float x,y,z,w;
    } __attribute__ ((aligned(16)));
    
};

#include "Vector3.inl"
#endif
