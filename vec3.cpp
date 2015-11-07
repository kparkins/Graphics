#include "vec3.h"

vec3::vec3() {
    _mm_store_ps(&x, _mm_set1_ps(0.f));
}

vec3::vec3(float m0, float m1, float m2) {
    x = m0;
    y = m1;
    z = m2;
}

vec3::~vec3() {
    //
}

vec4 vec3::toVector4(float w) const {
    return vec4(x, y, z, w);
}

void vec3::print(const std::string & comment) const {
    std::cout << comment << std::endl;
    std::cout << "<x:" << x << ", y:" << y << ", z:" << z << ">" << std::endl;
}