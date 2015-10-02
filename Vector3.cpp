#include "Vector3.h"
#include "Vector4.h"

Vector3::Vector3() {
    m[0] = 0;
    m[1] = 0;
    m[2] = 0;
}

Vector3::Vector3(float m0, float m1, float m2) {
    m[0] = m0;
    m[1] = m1;
    m[2] = m2;
}

Vector3::~Vector3() {
    //
}

Vector4 Vector3::toVector4(float w) {
    return Vector4(m[0], m[1], m[2], w);
}


