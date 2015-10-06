#ifndef VECTOR3_H
#define VECTOR3_H

#include <string>
#include <math.h>
#include <cassert>
#include <iostream>
#include <cstring>

#include "immintrin.h"
#include "Macros.h"
#include "Vector4.h"

class Vector4;

class Vector3 {

public:

    Vector3();
    Vector3(float, float, float);
    virtual ~Vector3(void);

    force_inline void set(float, float, float);

    force_inline float* ptr();
    force_inline float& operator[](int);

    force_inline Vector3& operator*=(const Vector3&);
    force_inline Vector3& operator+=(const Vector3&);
    force_inline Vector3& operator-=(const Vector3&);
    force_inline Vector3& operator=(const Vector3&);

    force_inline Vector3& operator*=(float);
    force_inline Vector3& operator+=(float);
    force_inline Vector3& operator-=(float);
    force_inline Vector3& operator=(float);

    force_inline Vector3 add(const Vector3 &) const;
    force_inline Vector3 operator+(const Vector3 &) const;

    force_inline Vector3 subtract(const Vector3 &) const;
    force_inline Vector3 operator-(const Vector3 &) const;

    force_inline Vector3 negate(void) const;
    force_inline Vector3 scale(float) const;
    force_inline Vector3 multiply(float) const;
    force_inline Vector3 operator*(float) const;
    force_inline Vector3 multiply(const Vector3 &) const;
    force_inline Vector3 operator*(const Vector3 &) const;

    force_inline float dot(const Vector3 &);
    force_inline Vector3 cross(const Vector3 &);

    force_inline float angle(const Vector3 &);

    force_inline float magnitude(void) const;

    force_inline Vector3 normalize(void) const;

    Vector4 toVector4(float) const;

    void print(const std::string &)  const;

#if defined(__GNUC__) | defined(clang)
    struct {
        float x, y, z, w;
    } align_16;
#elif defined(_MSC_VER)
    align_16 struct {
        float x, y, z, w;
    };
#endif

};

#include "Vector3.inl"
#endif
