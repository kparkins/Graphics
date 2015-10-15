//
// Created by Kyle J Parkinson on 10/12/15.
//

#ifndef CUBE_RASTERIZER_H
#define CUBE_RASTERIZER_H

#include "Matrix4.h"
#include "Window.h"
#include "Globals.h"

using std::min;

class Rasterizer {

public:

    static void enable();
    static void disable();

    static Matrix4 m_viewport;
    static Matrix4 m_projection;

private:

    static FORCE_INLINE bool inPixelArray(int x, int y);
    static FORCE_INLINE bool inTriangle(int x, int y, Vector3* v);
    static void idleCallback();
    static void displayCallback();
    static void reshapeCallback(int newWidth, int newHeight);
    static void rasterize();
    static Vector3 rasterizeVertex(float x, float y, float z, float w);
    static void rasterizeVertices();
    static void rasterizeTriangle(Vector3* v);
    static void rasterizeTriangles();
    static void drawPoint(int x, int , float r, float g, float b);
    static void clearBuffer();

    static float* m_pixels;
    static float* m_zbuffer;
    static int m_lastTime;
    static int m_windowWidth;
    static int m_windowHeight;

};

bool Rasterizer::inPixelArray(int x, int y) {
    return x >= 0 && x < m_windowWidth && y >= 0 && y < m_windowHeight;
}

bool Rasterizer::inTriangle(int x, int y, Vector3* v) {
    Vector3 v01 = v[1] - v[0];
    Vector3 v02 = v[2] - v[0];
    Vector3 v0p = Vector3(x, y, 1.f) - v[0];
    v01.z = 0.f;
    v02.z = 0.f;
    v0p.z = 0.f;
    float totalArea = v02.cross(v01).magnitude() * .5f;

    float alpha = (v0p.cross(v01).magnitude() * .5f) / totalArea;
    if(alpha <= 0.f || alpha >= 1.f) {
        return false;
    }

    float beta = (v02.cross(v0p).magnitude() * .5f) / totalArea;
    if(beta <= 0.f || beta >= 1.f) {
        return false;
    }

    float gamma = 1.f - alpha - beta;
    if(gamma <= 0.f || gamma >= 1.f) {
        return false;
    }


    int index = y * m_windowWidth + x;
    float z = alpha * v[0].z + beta * v[1].z + gamma * v[2].z;
    if(z > m_zbuffer[index]) {
        return false;
    }
    m_zbuffer[index] = z;
    return true;
}

#endif //CUBE_RASTERIZER_H
