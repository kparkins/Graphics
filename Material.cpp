#include "material.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

void gfx::apply(material & mat) {
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat.emissive.ptr());
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat.specular.ptr());
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat.diffuse.ptr());
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, mat.ambient.ptr());
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &mat.shininess);
}



