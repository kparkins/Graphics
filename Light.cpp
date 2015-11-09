#include "light.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

gfx::light::light() : m_id(-1) {
    m_ambient = color();
    m_diffuse = color();
    m_specular = color();

    m_directional = false;
    m_constantatt = 1.0;
    m_linearatt = 0.0;
    m_quadraticatt = 0.f;
    m_angle = -1.f;
    m_exponent = 1.f;
    m_direction = vec3(0.f, 0.f, 0.f) - vec3(m_position.x, m_position.y, m_position.z);
}

gfx::light::~light() {

}

void gfx::light::bind(int id) {
    if(id < 0 || id > 7) {
        std::cout << "ERROR: The light bind ID " << id << " is not valid!" << std::endl;
        return;
    }
    
    //Set the m_id
    m_id = id;
    
    //Configure the light at the m_id
    glEnable(GL_LIGHT0 + m_id);
    
    //Configure the m_color of the light
    glLightfv(GL_LIGHT0 + m_id, GL_AMBIENT, m_ambient.ptr());
    glLightfv(GL_LIGHT0 + m_id, GL_DIFFUSE, m_diffuse.ptr());
    glLightfv(GL_LIGHT0 + m_id, GL_SPECULAR, m_specular.ptr());

    //Configure the attenuation properties of the light
    glLightf(GL_LIGHT0 + m_id, GL_QUADRATIC_ATTENUATION, m_quadraticatt);
    glLightf(GL_LIGHT0 + m_id, GL_LINEAR_ATTENUATION, m_linearatt);
    glLightf(GL_LIGHT0 + m_id, GL_CONSTANT_ATTENUATION, m_constantatt);

    //Position the light
    glLightfv(GL_LIGHT0 + m_id, GL_POSITION, m_position.ptr());

    //Setup spotlight direction, angle, and exponent here
    if(m_angle >= 0.f) {
        glLightf(GL_LIGHT0 + m_id, GL_SPOT_EXPONENT, m_exponent);
        glLightf(GL_LIGHT0 + m_id, GL_SPOT_CUTOFF, m_angle);
    }

    if(m_directional) {
        glLightfv(GL_LIGHT0 + m_id, GL_SPOT_DIRECTION, m_direction.ptr());
    }
}

void gfx::light::unbind(void) {
    glDisable(GL_LIGHT0 + m_id);
    m_id = -1;
}

void gfx::light::angle(float angle) {
    this->m_angle = angle;
}

void gfx::light::exponent(float exp) {
    this->m_exponent = exp;
}

void gfx::light::direction(const vec3 & lookAt) {
    this->m_direction = lookAt - vec3(m_position.x, m_position.y, m_position.z);
}

void gfx::light::position(const vec4 & pos) {
    this->m_position = pos;
}

gfx::vec4 gfx::light::position() {
    return this->m_position;
}

void gfx::light::directional(bool on) {
    this->m_directional = on;
}

float gfx::light::constant_attenuation() {
    return this->m_constantatt;
}

float gfx::light::linear_attenuation() {
    return this->m_linearatt;
}

float gfx::light::quadratic_attentuation() {
    return this->m_quadraticatt;
}

void gfx::light::constant_attenuation(float c) {
    this->m_constantatt = c;
}

void gfx::light::linear_attenuation(float c) {
    this->m_linearatt = c;
}

void gfx::light::quadratic_attentuation(float c) {
    this->m_quadraticatt = c;
}

float gfx::light::angle() {
    return m_angle;
}

float gfx::light::exponent() {
    return m_exponent;
}
