//
// Created by Kyle J Parkinson on 10/29/15.
//

#ifndef GFX_MATERIALFACTORY_H
#define GFX_MATERIALFACTORY_H

#include <string>
#include <unordered_map>

#include "material.h"

using std::string;
using std::unordered_map;

using gfx::material;

namespace gfx {
    class material_factory {

    public:

        material_factory();
        ~material_factory();

        material_factory& ambient(color c);
        material_factory& ambient(float r, float g, float b, float a);
        material_factory& diffuse(color c);
        material_factory& diffuse(float r, float g, float b, float a);
        material_factory& specular(color c);
        material_factory& specular(float r, float g, float b, float a);
        material_factory& emissive(color c);
        material_factory& emissive(float r, float g, float b, float a);
        material_factory& shinniness(float s);

        gfx::material make(const string &material);
        gfx::material build();

        void clear();
        void save(const string &name);
        bool load(const string &material);

        static gfx::material get(const string & material);

    private:

        gfx::material m_material;
        unordered_map<string, material> m_materials;

    };
}
#endif
