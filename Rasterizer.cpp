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

int Rasterizer::m_windowWidth = 512;
int Rasterizer::m_windowHeight = 512;
float* Rasterizer::m_pixels = new float[m_windowWidth * m_windowHeight * 3];
Matrix4 Rasterizer::m_viewport = Rasterizer::m_viewport.makeViewport(0.f, 512.f, 0.f, 512.f);
Matrix4 Rasterizer::m_projection = Rasterizer::m_projection.makePerspectiveProjection(M_PI / 3.f, 512.f, 512.f, 1.f, 1000.f);
int Rasterizer::m_lastTime = 0;

using namespace std;

void Rasterizer::clearBuffer() {
    for (int i=0; i<m_windowWidth*m_windowHeight; ++i) {
        m_pixels[i*3]   = 0.f;
        m_pixels[i*3+1] = 0.f;
        m_pixels[i*3+2] = 0.f;
    }
}

void Rasterizer::drawPoint(int x, int y, float r, float g, float b) {
    int offset = y * m_windowWidth * 3 + x * 3;
    if(!inPixelArray(x, y)) {
        return;
    }
    m_pixels[offset]   = r;
    m_pixels[offset+1] = g;
    m_pixels[offset+2] = b;
}

Vector4 Rasterizer::rasterizeVertex(float x, float y, float z, float w) {
    Vector4 vertex(x, y, z, w);
    vertex = m_projection * Globals::camera.getInverseMatrix() * Window::m_model->m_toWorld * vertex;
    vertex = m_viewport * vertex.dehomogenize();
    return vertex;
}

void Rasterizer::rasterizeVertices() {
    Vector4 vertex;
    const vector<float> & vertices = Window::m_model->getVertexArray();
    for(int i = 0; i < vertices.size(); i += 3) {
        vertex = rasterizeVertex(vertices[i], vertices[i + 1], vertices[i + 2], 1.f);
        drawPoint(vertex.x, vertex.y, 1.f, 1.f, 1.f);
    }
}

void Rasterizer::rasterizeTriangle(Vector4* v) {
    Vector3 bBoxMin(std::min(std::min(v[0].x, v[1].x), v[2].x),
                    std::min(std::min(v[0].y, v[1].y), v[2].y), 0.f);
    Vector3 bBoxMax(std::max(std::max(v[0].x, v[1].x), v[2].x),
                    std::max(std::max(v[0].y, v[1].y), v[2].y), 0.f);

}

void Rasterizer::rasterizeTriangles() {
    Vector4 v[3];
    const vector<float> & vertices = Window::m_model->getVertexArray();
    for(int j = 0; j < vertices.size(); j += 9) {
        v[0] = rasterizeVertex(vertices[j]    , vertices[j + 1], vertices[j + 2], 1.f);
        v[1] = rasterizeVertex(vertices[j + 3], vertices[j + 4], vertices[j + 5], 1.f);
        v[2] = rasterizeVertex(vertices[j + 6], vertices[j + 7], vertices[j + 8], 1.f);
    }
}

void Rasterizer::rasterize() {
    rasterizeVertices();
    rasterizeTriangles();
}

void Rasterizer::reshapeCallback(int new_width, int new_height) {
    m_windowWidth  = new_width;
    m_windowHeight = new_height;
    delete[] m_pixels;
    m_pixels = new float[m_windowWidth * m_windowHeight * 3];
    m_viewport.makeViewport(0.f, m_windowWidth, 0.f, m_windowHeight);
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

    glDrawPixels(m_windowWidth, m_windowHeight, GL_RGB, GL_FLOAT, m_pixels);

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