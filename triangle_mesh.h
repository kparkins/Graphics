#ifndef GFX_OBJOBJECT_H
#define GFX_OBJOBJECT_H

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
    #define glGenVertexArrays glGenVertexArraysAPPLE
    #define glBindVertexArray glBindVertexArrayAPPLE
    #define glDeleteVertexArrays glDeleteVertexArraysAPPLE
#else
#include <GL/glut.h>
#endif

#include <vector>
#include <string>
#include <memory>
#include <limits>
#include <fstream>
#include <sstream>
#include <iostream>

#include "vec3.h"

using std::string;
using std::vector;
using std::shared_ptr;

namespace gfx {
    class triangle_mesh {

    public:

        enum {
            VERTICES = 1 << 0,
            COLORS = 1 << 1,
            NORMALS = 1 << 2,
            TEXTURES = 1 << 3
        };

        triangle_mesh();
        virtual ~triangle_mesh(void);

        void generate_mesh(string);
        void buffer_mesh();
        void render();

        const vector<float>& vertices();
        void flatten();

    protected:

        unsigned int calculate_stride(unsigned int props);
        vector<string>& split(const string &, char, vector<string> &);

        vector<float> m_interleaved;
        vector<float> m_vertices;
        vector<float> m_normals;
        vector<float> m_colors;
        vector<int> m_faces;

        GLuint m_vbo;
        GLuint m_vao;

        size_t m_numverts;
        unsigned int m_properties;

    };

    typedef shared_ptr<triangle_mesh> triangle_mesh_ptr;
}
#endif
