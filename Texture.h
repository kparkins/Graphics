#ifndef GFX_TEXTURE_H
#define GFX_TEXTURE_H

#include <iostream>
#include <string>

namespace gfx {
    class texture {

    public:

        texture(void);
        texture(const char *filename);
        virtual ~texture(void);

        void bind(void);
        void unbind(void);

        unsigned int m_id;
        static texture *m_emptytexture;

    protected:

        const char *m_filename;
        static unsigned char *loadppm(const char *, int &, int &);

    };
}
#endif
