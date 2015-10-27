#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include "Drawable.h"
#include "Vector3.h"

class Sphere : public Drawable {
    
public:

    Sphere(double, int, int);

    void setRadius(double radius);
    void setSlices(int slices);
    void setStacks(int stacks);
    
    virtual void draw(DrawData&);
    virtual void update(UpdateData&);

protected:

    double m_radius;
    int m_slices, m_stacks;

};

#endif
