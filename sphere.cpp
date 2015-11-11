#include "sphere.h"

gfx::sphere::sphere(double radius, int slices, int stacks) {
    this->m_radius = radius;
    this->m_slices = slices;
    this->m_stacks = stacks;
}

void gfx::sphere::render() {
    glutSolidSphere(m_radius, m_slices, m_stacks);
}

