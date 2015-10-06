#ifndef VECTOR4_H
#define VECTOR4_H

#include <string>
#include <math.h>
#include <iostream>
#include <cstring>

#include "immintrin.h"
#include "Macros.h"

class Vector3;

class Vector4 {

public:

    Vector4();
    Vector4(float, float, float);
    Vector4(float, float, float, float);

    force_inline void set(float, float, float, float);

    force_inline float* ptr();
    force_inline float& operator[](int);

    force_inline Vector4 add(const Vector4 &) const;
    force_inline Vector4 operator+(const Vector4 &) const;

    force_inline Vector4 subtract(const Vector4 &) const;
    force_inline Vector4 operator-(const Vector4 &) const;

    force_inline Vector4 dehomogenize() const;

    Vector3 toVector3();

    force_inline float dot(const Vector4 &) const;

    void print(const std::string &) const;

#if defined(__GNUC__) | defined(__clang__)
    struct {
        float x, y, z, w;
    } align_16;
#elif defined(_MSC_VER)
    align_16 struct {
        float x, y, z, w;
    };
#endif

};

#include "Vector4.inl"
#endif
