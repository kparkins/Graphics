#ifndef GFX_TEXTURE_H
#define GFX_TEXTURE_H

#include <memory>
#include <iostream>
#include <string>

using std::shared_ptr;

namespace gfx {
    class texture {

    public:

        texture();
        texture(const char *filename);
        virtual ~texture(void);

        void bind(void);
        void unbind(void);

        static texture *m_emptytexture;

        static unsigned char *loadppm(const char *, int &, int &);

    protected:

        unsigned int m_id;
        const char *m_filename;

    };

    typedef shared_ptr<texture> texture_ptr;
}
#endif
