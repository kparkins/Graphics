#ifndef GFX_TEXTURE_LOADER_H
#define GFX_TEXTURE_LOADER_H

#include <string>

#include "SOIL.h"
#include  "texture.h"

using std::string;

namespace gfx {
    class texture_loader {

    public:

        enum {
            SQUARE,
            HORIZONTAL_CROSS
        };

        texture_loader();
        ~texture_loader();

        texture_ptr load(const string & filename, unsigned int format);

    private:

    };
}
#endif