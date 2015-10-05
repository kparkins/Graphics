#include "Light.h"
#include "Window.h"
#include <iostream>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


Light::Light() : m_bindID(-1) {
    m_ambientColor = Color::ambientDefault();
    m_diffuseColor = Color::diffuseDefault();
    m_specularColor = Color::specularDefault();
    
    m_constantAttenuation = 1.0;
    m_linearAttenuation = 0.0;
    m_quadraticAttenuation = 0.05;
}

Light::~Light() {
    //Delete any dynamically allocated memory/objects here
}

void Light::bind(int id) {
    if(id < 0 || id > 7) {
        std::cout << "ERROR: The light bind ID " << id << " is not valid!" << std::endl;
        return;
    }
    
    //Set the m_bindID
    m_bindID = id;
    
    //Configure the light at the m_bindID
    glEnable(GL_LIGHT0 + m_bindID);
    
    //Configure the m_color of the light
    glLightfv(GL_LIGHT0 + m_bindID, GL_AMBIENT, m_ambientColor.ptr());
    glLightfv(GL_LIGHT0 + m_bindID, GL_DIFFUSE, m_diffuseColor.ptr());
    glLightfv(GL_LIGHT0 + m_bindID, GL_SPECULAR, m_specularColor.ptr());
    
    //Configure the attenuation properties of the light
    //Add support for Constant Attenuation
    //Add support for Linear Attenuation
    glLightf(GL_LIGHT0 + m_bindID, GL_QUADRATIC_ATTENUATION, m_quadraticAttenuation);
    
    //Position the light
    glLightfv(GL_LIGHT0 + m_bindID, GL_POSITION, m_position.ptr());
    
    //Setup spotlight direction, angle, and exponent here
}

void Light::unbind(void) {
    glDisable(GL_LIGHT0 + m_bindID);
    m_bindID = -1;
}
