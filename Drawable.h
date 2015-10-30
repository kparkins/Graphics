#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <iostream>
#include "Matrix4.h"
#include "DrawData.h"
#include "UpdateData.h"
#include "Material.h"
#include <float.h>
#include <math.h>
#include <vector>
#include <memory>

using std::vector;

typedef struct BoundingBox {
    float xmin, ymin, zmin;
    float xmax, ymax, zmax;
}BoundingBox;

class Drawable {
    
public:
    
    Matrix4 m_toWorld;
    Material m_material;
    float m_rotationY;

    Drawable(void);
    ~Drawable(void);
    
    virtual void draw(DrawData&);
    virtual void update(UpdateData&);
    virtual void computeBoundingBox();
    virtual void translateToOrigin();

    const vector<float>& getVertexArray();

protected:

    BoundingBox m_box;
    vector<float> m_vertexArray;

};

typedef std::shared_ptr<Drawable> DrawablePtr;

#endif
