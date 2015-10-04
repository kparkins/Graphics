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


class Drawable {
    
public:
    
    Matrix4 toWorld;
    Material material;
    
    Drawable(void);
    ~Drawable(void);
    
    virtual void draw(DrawData&);
    virtual void update(UpdateData&);
    
};

#endif
