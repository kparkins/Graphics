#include "cube.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

gfx::cube::cube(float size) {
    this->m_size = size;
}

gfx::cube::cube() {
    this->m_size = 1.f;
}

gfx::cube::~cube() {
    //Delete any dynamically allocated memory/objects here
}

void gfx::cube::render() {
    glutSolidCube(m_size);
}

