#include "Vector3.h"
#include "Vector4.h"

Vector3::Vector3() {
	_mm_store_ps(&x, _mm_set1_ps(0.f));
}

Vector3::Vector3(float m0, float m1, float m2) {
    x = m0;
    y = m1;
    z = m2;
}

Vector3::~Vector3() {
    //
}

Vector4 Vector3::toVector4(float w) const {
    return Vector4(x, y, z, w);
}

void Vector3::print(const std::string & comment) const {
    std::cout << comment << std::endl;
    std::cout << "<x:" << x <<  ", y:" << y << ", z:" << z << ">" << std::endl;
}