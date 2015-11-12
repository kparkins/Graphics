#ifndef GFX_NODE_H
#define GFX_NODE_H

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

#include "mat4.h"
#include "vec3.h"

using std::shared_ptr;

namespace gfx {
    class node {

    public:

        virtual ~node();

        virtual void draw(mat4 &c) = 0;

    };

    typedef shared_ptr<node> node_ptr;
}

#endif