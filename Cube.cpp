#include "Cube.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

Cube::Cube(float size) {
    this->m_size = size;
}

Cube::Cube() {
    this->m_size = 1.f;
}

Cube::~Cube() {
    //Delete any dynamically allocated memory/objects here
}


void Cube::render() {
    glutSolidCube(m_size);
}

