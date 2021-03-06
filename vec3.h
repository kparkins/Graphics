#ifndef GFX_VECTOR3_H
#define GFX_VECTOR3_H

#include <string>
#include <math.h>
#include <cassert>
#include <iostream>
#include <cstring>

#include "immintrin.h"
#include "macros.h"

namespace gfx {

    class vec4;

    class vec3 {

    public:

        vec3();
        vec3(float, float, float);
        virtual ~vec3(void);

        FORCE_INLINE void set(float, float, float);
        FORCE_INLINE float *ptr();
        FORCE_INLINE float &operator[](int);
        FORCE_INLINE vec3 &operator*=(const vec3 &);
        FORCE_INLINE vec3 &operator+=(const vec3 &);
        FORCE_INLINE vec3 &operator-=(const vec3 &);
        FORCE_INLINE vec3 &operator=(const vec3 &);
        FORCE_INLINE vec3 &operator*=(float);
        FORCE_INLINE vec3 &operator+=(float);
        FORCE_INLINE vec3 &operator-=(float);
        FORCE_INLINE vec3 &operator=(float);
        FORCE_INLINE vec3 add(const vec3 &) const;
        FORCE_INLINE vec3 operator+(const vec3 &) const;
        FORCE_INLINE vec3 subtract(const vec3 &) const;
        FORCE_INLINE vec3 operator-(const vec3 &) const;
        FORCE_INLINE vec3 negate() const;
        FORCE_INLINE vec3 scale(float) const;
        FORCE_INLINE vec3 multiply(float) const;
        FORCE_INLINE vec3 operator*(float) const;
        FORCE_INLINE vec3 multiply(const vec3 &) const;
        FORCE_INLINE vec3 operator*(const vec3 &) const;
        FORCE_INLINE float dot(const vec3 &);
        FORCE_INLINE vec3 cross(const vec3 &);
        FORCE_INLINE float angle(const vec3 &);
        FORCE_INLINE float magnitude() const;
        FORCE_INLINE vec3 &normalize();
        FORCE_INLINE vec3 normalized() const;

        gfx::vec4 to_vec4(float) const;

        void print(const std::string &) const;

#if defined(__GNUC__) || defined(clang)
        struct {
            float x, y, z, w;
        } ALIGN_16;
#elif defined(_MSC_VER)
        ALIGN_16 struct {
            float x, y, z, w;
        };
#endif

    };
}
#include "vec3.inl"
#endif
