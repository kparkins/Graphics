#ifndef GFX_MATRIX4_H
#define GFX_MATRIX4_H

#include <string>
#include <math.h>
#include <cassert>
#include <iomanip>
#include <cstring>
#include <iostream>

#include "immintrin.h"
#include "macros.h"

class vec3;
class vec4;

namespace gfx {
    class mat4 {

    public:

        mat4();
        mat4(float, float, float, float,
                float, float, float, float,
                float, float, float, float,
                float, float, float, float);

        FORCE_INLINE void set(float, float, float, float,
                              float, float, float, float,
                              float, float, float, float,
                              float, float, float, float);

        FORCE_INLINE float get(int,int);

        FORCE_INLINE mat4 & operator=(const mat4 &);

        FORCE_INLINE float* operator[](int);

        FORCE_INLINE float* ptr();

        FORCE_INLINE mat4 & identity();

        FORCE_INLINE mat4 multiply(const mat4 &);
        FORCE_INLINE mat4 operator*(const mat4 &);

        vec4 multiply(vec4 &);
        vec4 operator*(vec4 &);
        vec3 multiply(vec3 &);
        vec3 operator*(vec3 &);

        FORCE_INLINE mat4 & rotatex(float);
        FORCE_INLINE mat4 & rotatey(float);
        FORCE_INLINE mat4 &rotatez(float);
        mat4 & rotate_arbitrary(const vec3 &, float);

        FORCE_INLINE mat4 & scale(float, float, float);
        FORCE_INLINE mat4 & scale(float);

        FORCE_INLINE mat4 & translate(float, float, float);
        mat4 & translate(const vec3 &);

        mat4 transpose(void);
        mat4 inverse(void);
        mat4 rigid_inverse(void);

        mat4 & perspective_projection(float, float, float, float, float);
        mat4 & viewport(float, float, float, float);

        void print(const std::string &);

        ALIGN_16 float m[4][4];

    };
}

#include "mat4.inl"
#endif
