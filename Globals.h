#ifndef CUBE_GLOBALS_H
#define CUBE_GLOBALS_H

#include "Vector3.h"

class Plane {

public:

    Vector3 normal;
    Vector3 point;
    float d;

    void set(Vector3 a, Vector3 b, Vector3 c) {
        Vector3 normal = (c - b).cross(a - b);
        normal.normalize();

        point = b;
        d = -1 * normal.dot(point);
    }

    float distance(Vector3 & point) {
        return d + normal.dot(point);
    }

    void setNormalAndPoint(Vector3 & normal, Vector3 & point) {
        this->normal = normal;
        this->normal.normalize();
        d = -1 * this->normal.dot(point);
    }

};

class Frustrum {

public:

    enum {
        TOP = 0,
        BOTTOM,
        LEFT,
        RIGHT,
        NEAR,
        FAR
    };

    bool sphereInFrustrum(Vector3 origin, float radius) {
        float d = 0.f;
        bool result = true;
        for(int i = 0; i < 6; ++i) {
            d = planes[i].distance(origin);
            if(d < -1 * radius) {
                return false;
            }
        }
        return true;
    }

    float fov;
    float halfFov;
    float aspect;
    float nearPlane;
    float farPlane;
    float nearHeight;
    float nearWidth;
    float farHeight;
    float farWidth;
    Vector3 farCenter;
    Vector3 nearCenter;
    Vector3 e;
    Vector3 d;
    Vector3 up;

    Vector3 z;
    Vector3 x;
    Vector3 y;
    Vector3 farTopLeft;
    Vector3 farTopRight;
    Vector3 farBottomLeft;
    Vector3 farBottomRight;
    Vector3 nearTopLeft;
    Vector3 nearTopRight;
    Vector3 nearBottomLeft;
    Vector3 nearBottomRight;

    Plane planes[6];
};

class Globals {

public:

    static bool enableCulling;
    static bool drawBoundingSphere;

};


#endif