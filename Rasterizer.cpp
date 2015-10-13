//
// Created by Kyle J Parkinson on 10/12/15.
//

#include <math.h>
#include "Rasterizer.h"
#include "Window.h"
#include "Globals.h"

#ifdef _WIN32
#include <windows.h>
#endif
#include <iostream>
#include <GLUT/glut.h>

static int window_width = 512, window_height = 512;
static float* pixels = new float[window_width * window_height * 3];
Matrix4 Rasterizer::m_viewport = Rasterizer::m_viewport.makeViewport(0.f, 512.f, 0.f, 512.f);
Matrix4 Rasterizer::m_projection = Rasterizer::m_projection.makePerspectiveProjection(M_PI / 3.f, 512.f, 512.f, 1.f, 1000.f);
int Rasterizer::m_lastTime = 0;

using namespace std;

// Clear frame buffer
void Rasterizer::clearBuffer() {
    for (int i=0; i<window_width*window_height; ++i) {
        pixels[i*3]   = 0.f;
        pixels[i*3+1] = 0.f;
        pixels[i*3+2] = 0.f;
    }
}

// Draw a point into the frame buffer
void Rasterizer::drawPoint(int x, int y, float r, float g, float b) {
    int offset = y*window_width*3 + x*3;
    if(x < 0 || x >= window_width || y < 0 || y >= window_width) {
        return;
    }
    pixels[offset]   = r;
    pixels[offset+1] = g;
    pixels[offset+2] = b;
}

void Rasterizer::rasterizeTriangle() {
    // Add code to rasterize a triangle
}

void Rasterizer::rasterize() {
    // Put your main rasterization loop here
    // It should go over the data model and call rasterizeTriangle for every triangle in it

    Vector4 vertex;
    const vector<float> & vertices = Window::m_model->getVertexArray();
    for(int i = 0; i < vertices.size(); i += 3){
        vertex.set(vertices[i], vertices[i + 1], vertices[i + 2], 1.f);
        vertex = m_projection * Globals::camera.getInverseMatrix() * Window::m_model->m_toWorld * vertex;
        vertex = vertex.dehomogenize();
        vertex = m_viewport * vertex;
        drawPoint(vertex.x, vertex.y, 1.f, 1.f, 1.f);
    }

}

// Called whenever the window size changes
void Rasterizer::reshapeCallback(int new_width, int new_height) {
    window_width  = new_width;
    window_height = new_height;
    delete[] pixels;
    pixels = new float[window_width * window_height * 3];
    m_viewport.makeViewport(0.f, window_width, 0.f, window_height);
    m_projection.makePerspectiveProjection(M_PI / 3.f, new_width, new_height, 1.f, 1000.f);
}


void Rasterizer::displayCallback() {
    static int frame;
    frame++;
    int newTime = glutGet(GLUT_ELAPSED_TIME);
    if(newTime - m_lastTime > 1000) {
        std::cout << "fps\t" << frame * 1000 / (newTime - m_lastTime) << std::endl;
        m_lastTime = newTime;
        frame = 0;
    }
    clearBuffer();
    rasterize();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // glDrawPixels writes a block of pixels to the framebuffer
    glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, pixels);

    glutSwapBuffers();
}

void Rasterizer::idleCallback() {
    displayCallback();
}

void Rasterizer::disable() {
    glutDisplayFunc(&Window::displayCallback);
    glutIdleFunc(&Window::idleCallback);
    glutReshapeFunc(&Window::reshapeCallback);
}

void Rasterizer::enable() {

    glutReshapeFunc(reshapeCallback);
    glutDisplayFunc(displayCallback);
    glutIdleFunc(idleCallback);

    glEnable(GL_DEPTH_TEST);

    glClearColor(0.0, 0.0, 0.0, 1.0);
}