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

    FORCE_INLINE void set(float, float, float);

    FORCE_INLINE float* ptr();
    FORCE_INLINE float& operator[](int);

    FORCE_INLINE Vector3& operator*=(const Vector3&);
    FORCE_INLINE Vector3& operator+=(const Vector3&);
    FORCE_INLINE Vector3& operator-=(const Vector3&);
    FORCE_INLINE Vector3& operator=(const Vector3&);

    FORCE_INLINE Vector3& operator*=(float);
    FORCE_INLINE Vector3& operator+=(float);
    FORCE_INLINE Vector3& operator-=(float);
    FORCE_INLINE Vector3& operator=(float);

    FORCE_INLINE Vector3 add(const Vector3 &) const;
    FORCE_INLINE Vector3 operator+(const Vector3 &) const;

    FORCE_INLINE Vector3 subtract(const Vector3 &) const;
    FORCE_INLINE Vector3 operator-(const Vector3 &) const;

    FORCE_INLINE Vector3 negate(void) const;
    FORCE_INLINE Vector3 scale(float) const;
    FORCE_INLINE Vector3 multiply(float) const;
    FORCE_INLINE Vector3 operator*(float) const;
    FORCE_INLINE Vector3 multiply(const Vector3 &) const;
    FORCE_INLINE Vector3 operator*(const Vector3 &) const;

    FORCE_INLINE float dot(const Vector3 &);
    FORCE_INLINE Vector3 cross(const Vector3 &);

    FORCE_INLINE float angle(const Vector3 &);

    FORCE_INLINE float magnitude(void) const;

    FORCE_INLINE Vector3& normalize(void);
    FORCE_INLINE Vector3 asNormalized() const;

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
