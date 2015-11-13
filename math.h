#ifndef GFX_MATH_H
#define GFX_MATH_H

#include <cmath>
#include <cassert>

#include "macros.h"

namespace gfx {
    namespace math {

        long factorial(unsigned int n);

        FORCE_INLINE float radians(float angle) {
            return static_cast<float>(M_PI * angle / 180.f);
        }
    }
}

#endif