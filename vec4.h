#ifndef GFX_VECTOR4_H
#define GFX_VECTOR4_H

#include <string>
#include <math.h>
#include <iostream>
#include <cstring>

#include "immintrin.h"
#include "macros.h"

namespace gfx {

    class vec3;

    class vec4 {

    public:

        vec4();

        vec4(float, float, float);

        vec4(float, float, float, float);

        FORCE_INLINE vec4 &set(float, float, float, float);
        FORCE_INLINE float *ptr();
        FORCE_INLINE float &operator[](int);
        FORCE_INLINE vec4 add(const vec4 &) const;
        FORCE_INLINE vec4 operator+(const vec4 &) const;
        FORCE_INLINE vec4 subtract(const vec4 &) const;
        FORCE_INLINE vec4 operator-(const vec4 &) const;
        FORCE_INLINE vec4 &dehomogenize();
        FORCE_INLINE float dot(const vec4 &) const;

        gfx::vec3 to_vec3();
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
}
#include "vec4.inl"
#endif
