#include "math.h"

long gfx::math::factorial(unsigned int n) {
    assert(n >= 0);
    long result = 1;
    for(unsigned int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}
