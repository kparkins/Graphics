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

    static void idleCallback();
    static void displayCallback();
    static void reshapeCallback(int newWidth, int newHeight);
    static void rasterize();
    static void rasterizeTriangle();
    static void drawPoint(int x, int , float r, float g, float b);
    static void clearBuffer();

    static int m_lastTime;

};


#endif //CUBE_RASTERIZER_H
