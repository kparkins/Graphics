#ifndef GFX_MATRIX_TRANSFORM_H
#define GFX_MATRIX_TRANSFORM_H

#include "group.h"
#include "material_factory.h"

namespace gfx {
    class matrix_transform : public group {

    public:

        matrix_transform();
        ~matrix_transform();

        void draw(mat4 &c) override;

        inline void transform(const mat4 & transform);
        inline mat4& transform();

    protected:

        mat4 m_transform;
        material m_material;

    };

    typedef shared_ptr<matrix_transform> matrix_transform_ptr;

    void matrix_transform::transform(const mat4 & transform) {
        this->m_transform = transform;
    }

    mat4& matrix_transform::transform() {
        return this->m_transform;
    }

}
#endif