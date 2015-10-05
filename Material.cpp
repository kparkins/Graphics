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
    
    //Set the initial m_color to a random pastel m_color
    //Can be removed once materials are implemented
    m_color = Color::randomPastel();
}

Material::~Material() {
    //Delete any dynamically allocated memory/objects here
}

void Material::apply(void) {
    //Set the m_material properties for ambient, diffuse, specular, emission, and m_shininess
    //Hint: Lookup how glMaterialfv works
    
    //Set the m_color property (can be removed once materials are implemented)
    //Used for projects 1, 2, and 3
    glColor3fv(m_color.ptr());
}



