#ifndef CUBE_MATRIXTRANSFORM_H
#define CUBE_MATRIXTRANSFORM_H

#include "Group.h"
#include "Matrix4.h"
#include "Globals.h"
#include "Material.h"

extern Frustrum frustrum;

class MatrixTransform : public Group {

public:

    MatrixTransform();
    ~MatrixTransform();

    void draw(Matrix4 & c) override;
    void setTransform(const Matrix4 & transform);
    Matrix4& getTransform();

protected:

    Matrix4 m_transform;
    Material m_material;
};

typedef shared_ptr<MatrixTransform> MatrixTransformPtr;

#endif