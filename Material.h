#ifndef GFX_MATERIAL_H
#define GFX_MATERIAL_H

#include <iostream>
#include "color.h"


namespace gfx {

    typedef struct material {
        color ambient;
        color diffuse;
        color specular;
        color emissive;
        float shininess;
    } material;

    void apply(material & mat);
}

#endif
