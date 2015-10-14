//
// Created by Kyle J Parkinson on 10/12/15.
//

#ifndef CUBE_RASTERIZER_H
#define CUBE_RASTERIZER_H

#include "Matrix4.h"

class Rasterizer {

public:

    static void enable();
    static void disable();

    static Matrix4 m_viewport;
    static Matrix4 m_projection;

private:

    static FORCE_INLINE bool inPixelArray(int x, int y);
    static void idleCallback();
    static void displayCallback();
    static void reshapeCallback(int newWidth, int newHeight);
    static void rasterize();
    static Vector4 rasterizeVertex(float x, float y, float z, float w);
    static void rasterizeVertices();
    static void rasterizeTriangle(Vector4* v);
    static void rasterizeTriangles();
    static void drawPoint(int x, int , float r, float g, float b);
    static void clearBuffer();

    static float* m_pixels;
    static int m_lastTime;
    static int m_windowWidth;
    static int m_windowHeight;

};

bool Rasterizer::inPixelArray(int x, int y) {
    return !(x < 0 || x >= m_windowWidth || y < 0 || y >= m_windowHeight);
}

#endif //CUBE_RASTERIZER_H
