#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include "Drawable.h"
#include "Vector3.h"

class Sphere : public Drawable {
    
public:
    
    Vector3 m_velocity;
    double m_radius;
    int m_slices, m_stacks;
    
    Sphere(double, int, int);
    
    virtual void draw(DrawData&);
    virtual void update(UpdateData&);
    
};

#endif
