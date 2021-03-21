#ifndef GFX_TEXTURE_H
#define GFX_TEXTURE_H

#include <memory>
#include <iostream>
#include <string>
#include <OpenGL/OpenGL.h>

#include "SOIL.h"

using std::string;
using std::shared_ptr;

namespace gfx {
    class texture {

    public:

        texture();
        texture(const string & filename);
        virtual ~texture();

        void bind();
        void unbind();
        void generate(unsigned char* data, int width, int height);

        static unsigned char *loadppm(const char *, int &, int &);

    protected:

        GLuint m_id;

    };

    typedef shared_ptr<texture> texture_ptr;
}
#endif
