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

    FORCE_INLINE Vector4& set(float, float, float, float);

    FORCE_INLINE float* ptr();
    FORCE_INLINE float& operator[](int);

    FORCE_INLINE Vector4 add(const Vector4 &) const;
    FORCE_INLINE Vector4 operator+(const Vector4 &) const;

    FORCE_INLINE Vector4 subtract(const Vector4 &) const;
    FORCE_INLINE Vector4 operator-(const Vector4 &) const;

    FORCE_INLINE Vector4& dehomogenize();

    Vector3 toVector3();

    FORCE_INLINE float dot(const Vector4 &) const;

    void print(const std::string &) const;

#if defined(__GNUC__) || defined(__clang__)
    struct {
        float x, y, z, w;
    } ALIGN_16;
#elif defined(_MSC_VER)
    ALIGN_16 struct {
        float x, y, z, w;
    };
#endif

};

#include "Vector4.inl"
#endif
