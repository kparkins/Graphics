#include "Material.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

Material::Material() {
    //Material setup goes hurr
    m_ambientColor = Color::ambientMaterialDefault();
    m_diffuseColor = Color::diffuseMaterialDefault();
    m_specularColor = Color::specularMaterialDefault();
    m_emissionColor = Color::emissionMaterialDefault();
    m_shininess = 10.0;
}

Material::~Material() {
    //Delete any dynamically allocated memory/objects here
}

void Material::apply(void) {

    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, m_emissionColor.ptr());
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_specularColor.ptr());
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diffuseColor.ptr());
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, m_ambientColor.ptr());
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &m_shininess);
}



