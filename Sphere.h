#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include "Vector3.h"
#include "Geode.h"

class Sphere : public Geode {
    
public:

    Sphere(double, int, int);

    void setRadius(double radius);
    void setSlices(int slices);
    void setStacks(int stacks);
    
    void render() override;

protected:

    double m_radius;
    int m_slices, m_stacks;

};

#endif
