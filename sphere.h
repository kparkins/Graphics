#ifndef GFX_SPHERE_H
#define GFX_SPHERE_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

#include "vec3.h"
#include "geode.h"
#include "material_factory.h"

namespace gfx {
    class sphere : public geode {

    public:

        sphere(double, int, int);

        inline void radius(double radius);
        inline void slices(int slices);
        inline void stacks(int stacks);

        inline double radius();
        inline int slices();
        inline int stacks();

        void render() override;

    protected:

        double m_radius;
        int m_slices, m_stacks;

    };

    typedef shared_ptr<sphere> sphere_ptr;

    void sphere::radius(double radius) {
        this->m_radius = radius;
    }

    void sphere::slices(int slices) {
        this->m_slices = slices;
    }

    void sphere::stacks(int stacks) {
        this->m_stacks = stacks;
    }

}
#endif
