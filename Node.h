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

using std::shared_ptr;

class Node {

public:

    virtual ~Node();
    virtual void draw(Matrix4 & c) = 0;

};

typedef shared_ptr<Node> NodePtr;

#endif