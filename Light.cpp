#include "Light.h"
#include "Window.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

Light::Light() : m_bindID(-1) {
    MaterialFactory materialFactory;
    m_ambientColor = Color::black();
    m_diffuseColor = Color::white();
    m_specularColor = Color::white();

    m_directional = false;
    m_constantAttenuation = 1.0;
    m_linearAttenuation = 0.0;
    m_quadraticAttenuation = 0.f;
    m_spotAngle = 0.f;
    m_spotExponent = 1.f;
    m_spotDirection = Vector3(0.f, 0.f, 0.f) - m_position.toVector3();
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
    glLightf(GL_LIGHT0 + m_bindID, GL_QUADRATIC_ATTENUATION, m_quadraticAttenuation);
    glLightf(GL_LIGHT0 + m_bindID, GL_LINEAR_ATTENUATION, m_linearAttenuation);
    glLightf(GL_LIGHT0 + m_bindID, GL_CONSTANT_ATTENUATION, m_constantAttenuation);
    
    //Position the light
    glLightfv(GL_LIGHT0 + m_bindID, GL_POSITION, m_position.ptr());
    
    //Setup spotlight direction, angle, and exponent here
    if(m_spotAngle) {
        glLightf(GL_LIGHT0 + m_bindID, GL_SPOT_EXPONENT, m_spotExponent);
        glLightf(GL_LIGHT0 + m_bindID, GL_SPOT_CUTOFF, m_spotAngle);
    }

    if(m_directional) {
        glLightfv(GL_LIGHT0 + m_bindID, GL_SPOT_DIRECTION, m_spotDirection.ptr());
    }
}

void Light::unbind(void) {
    glDisable(GL_LIGHT0 + m_bindID);
    m_bindID = -1;
}

void Light::setSpotAngle(float angle) {
    this->m_spotAngle = angle;
}

void Light::setSpotExponent(float exp) {
    this->m_spotExponent = exp;
}

void Light::setSpotDirection(const Vector3 & lookAt) {
    this->m_spotDirection = lookAt - m_position.toVector3();
}

void Light::setPosition(const Vector4 & pos) {
    this->m_position = pos;
}

Vector4 Light::getPosition() {
    return this->m_position;
}

void Light::setDirectional(bool on) {
    this->m_directional = on;
}

float Light::getConstantAttenuation() {
    return this->m_constantAttenuation;
}

float Light::getLinearAttenuation() {
    return this->m_linearAttenuation;
}

float Light::getQuadraticAttentuation() {
    return this->m_quadraticAttenuation;
}

void Light::setConstantAttenuation(float c) {
    this->m_constantAttenuation = c;
}

void Light::setLinearAttenuation(float c) {
    this->m_linearAttenuation = c;
}

void Light::setQuadraticAttentuation(float c) {
    this->m_quadraticAttenuation = c;
}

float Light::getSpotAngle() {
    return m_spotAngle;
}

float Light::getSpotExponent() {
    return m_spotExponent;
}
