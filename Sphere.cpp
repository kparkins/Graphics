#include "Sphere.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

Sphere::Sphere(double radius, int slices, int stacks) {
    this->m_radius = radius;
    this->m_slices = slices;
    this->m_stacks = stacks;
}

void Sphere::setRadius(double radius) {
    this->m_radius = radius;
}

void Sphere::setSlices(int slices) {
    this->m_slices = slices;
}

void Sphere::setStacks(int stacks) {
    this->m_stacks = stacks;
}

void Sphere::render() {

}

