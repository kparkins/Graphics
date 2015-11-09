#include "vec3.h"

gfx::vec3::vec3() {
    _mm_store_ps(&x, _mm_set1_ps(0.f));
}

gfx::vec3::vec3(float m0, float m1, float m2) {
    x = m0;
    y = m1;
    z = m2;
}

gfx::vec3::~vec3() {
    //
}

gfx::vec4 gfx::vec3::to_vec4(float w) const {
    return vec4(x, y, z, w);
}

void gfx::vec3::print(const std::string & comment) const {
    std::cout << comment << std::endl;
    std::cout << "<x:" << x << ", y:" << y << ", z:" << z << ">" << std::endl;
}