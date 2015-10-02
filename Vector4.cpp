#include "Vector4.h"
#include "Vector3.h"

Vector4::Vector4() {
  memset(static_cast<void*>(&m), 0, sizeof(float) * 4);
}

Vector4::Vector4(float m0, float m1, float m2) {
    m[0] = m0;
    m[1] = m1;
    m[2] = m2;
    m[3] = 1;
}

Vector4::Vector4(float m0, float m1, float m2, float m3) {
    m[0] = m0;
    m[1] = m1;
    m[2] = m2;
    m[3] = m3;
}

Vector3 Vector4::toVector3() {
    return Vector3(m[0], m[1], m[2]);
}


