#ifndef GFX_BEZIER_PATCH_H
#define GFX_BEZIER_PATCH_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>
#include <memory>

#include "mat4.h"
#include "vec4.h"
#include "math.h"
#include "grid.h"
#include "shader.h"
#include "texture.h"

using std::shared_ptr;

namespace gfx {
    class bezier_patch {

    public:

        bezier_patch(size_t fidelity);
        ~bezier_patch();

        void fidelity(size_t f);
        size_t fidelity();

        void texture(texture_ptr t);
        texture_ptr texture();

        void generate();
        void draw(mat4 & c);

        inline vec4*operator[](size_t row);

    protected:

        vec4 eval_curve(float t, const vec4 & p0, const vec4 & p1, const vec4 & p2, const vec4 & p3);

        size_t m_fidelity;
        grid<vec4> m_vertices;
        grid<vec4> m_normals;
        grid<vec4> m_controlpoints;
        grid<vec3> m_texcoords;

        shader_ptr m_shader;
        texture_ptr m_texture;

    };

    inline vec4* gfx::bezier_patch::operator[](size_t row) {
        return &m_controlpoints[row][0];
    }

    typedef shared_ptr<bezier_patch> bezier_patch_ptr;
}
#endif