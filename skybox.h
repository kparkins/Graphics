#ifndef GFX_SKYBOX_H
#define GFX_SKYBOX_H

#include <string>
#include <vector>

#include "SOIL.h"
#include "cube.h"
#include "texture.h"

using std::string;
using std::vector;
using std::make_shared;

using gfx::cube;
using gfx::texture;

namespace gfx {
    class skybox {

    public:
        enum {
            LEFT = 0,
            FRONT = 1,
            RIGHT = 2,
            BACK = 3,
            TOP = 4,
            BOTTOM = 5,
        };

        skybox();
        ~skybox();

        void draw(mat4 & c);
        void sides(const vector<texture_ptr> & sides);
        void load(const vector<string> & images);

    protected:

        static float m_vertices[72];
        static float m_texcoords[48];
        vector<texture_ptr> m_sides;

    };

}
#endif