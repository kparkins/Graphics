#ifndef CUBE_NODE_H
#define CUBE_NODE_H

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#define glGenVertexArrays glGenVertexArraysAPPLE
#define glBindVertexArray glBindVertexArrayAPPLE
#define glDeleteVertexArrays glDeleteVertexArraysAPPLE
#else
#include <GL/glut.h>
#endif

#include <memory>

#include "Matrix4.h"
#include "Vector3.h"

using std::shared_ptr;

typedef struct BoundingSphere {
    Vector3 origin;
    float radius;
}BoundingSphere;

class Node {

public:

    Node();
    virtual ~Node();
    virtual void draw(Matrix4 & c) = 0;
    virtual void update(float dt) = 0;
    BoundingSphere getBoundingSphere();
    virtual void drawBoundingSphere();

    Matrix4 m_c;
    bool m_cull;
    bool m_bs;
    BoundingSphere m_boundingSphere;

};

typedef shared_ptr<Node> NodePtr;

#endif