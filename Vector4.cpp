#include "Vector4.h"
#include "Vector3.h"

Vector4::Vector4() {
  memset(static_cast<void*>(&x), 0, sizeof(float) * 4);
}

Vector4::Vector4(float m0, float m1, float m2) {
    x = m0;
    y = m1;
    z = m2;
    w = 1;
}

Vector4::Vector4(float m0, float m1, float m2, float m3) {
    x = m0;
    y = m1;
    z = m2;
    w = m3;
}

Vector3 Vector4::toVector3() {
    return Vector3(x, y, z);
}


