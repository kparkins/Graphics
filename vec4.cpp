#include "vec4.h"
#include "vec3.h"

gfx::vec4::vec4() {
    memset(static_cast<void*>(&x), 0, sizeof(float) * 4);
}

gfx::vec4::vec4(float m0, float m1, float m2) {
    x = m0;
    y = m1;
    z = m2;
    w = 1;
}

gfx::vec4::vec4(float m0, float m1, float m2, float m3) {
    x = m0;
    y = m1;
    z = m2;
    w = m3;
}

gfx::vec3 gfx::vec4::to_vec3() {
    return vec3(x, y, z);
}

void gfx::vec4::print(const std::string & comment) const {
    std::cout << comment << std::endl;
    std::cout << "<x:" << x << ", y:" << y << ", z:" << z << ", w:" << z << ">" << std::endl;
}
