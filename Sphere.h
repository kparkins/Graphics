#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include "Drawable.h"
#include "Vector3.h"

class Sphere : public Drawable {
    
public:
    
    Vector3 velocity;
    double radius;
    int slices, stacks;
    
    Sphere(double, int, int);
    
    virtual void draw(DrawData&);
    virtual void update(UpdateData&);
    
};

#endif
