#ifndef CUBE_PLATOON_H
#define CUBE_PLATOON_H

#include "MatrixTransform.h"
#include "Geode.h"

using std::make_shared;

class Platoon : public MatrixTransform {

public:

    Platoon(int rows, int cols, Vector3 origin, GeodePtr geom);
    ~Platoon();

    void draw(Matrix4 & c);

    void invertXOffset();

    int rows;
    int cols;
    float m_xOffsetSign;
    Vector3 origin;
    MatrixTransformPtr m_rotation;
    GeodePtr m_geometry;
};

typedef shared_ptr<Platoon> PlatoonPtr;

#endif