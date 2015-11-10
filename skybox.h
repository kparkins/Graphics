#ifndef GFX_SKYBOX_H
#define GFX_SKYBOX_H

#include <string>

#include "cube.h"
#include "texture.h"
#include "matrix_transform.h"

using std::string;

using gfx::cube;
using gfx::texture;

namespace gfx {
    class skybox : public matrix_transform {

    public:

        skybox(cube_ptr box);
        ~skybox();

    protected:

        cube_ptr m_skybox;

    };

}
#endif