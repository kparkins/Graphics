#ifndef GFX_GEODE_H
#define GFX_GEODE_H

#include "node.h"
#include "material_factory.h"


namespace gfx {
    class geode : public node {

    public:

        geode();
        virtual ~geode();

        virtual void render() = 0;

        void draw(mat4 &c) override;
        void update(float dt) override;

        inline void set_material(material &mat);

    protected:

        material m_material;

    };

    inline void geode::set_material(material & mat) {
        this->m_material = mat;
    }

    typedef shared_ptr<geode> geode_ptr;
}

#endif