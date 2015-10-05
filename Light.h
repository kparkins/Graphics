#ifndef LIGHT_H
#define LIGHT_H

#include "Matrix4.h"
#include "Vector4.h"
#include "Color.h"
#include <vector>

class Light {
 
public:
    
    Light();
    virtual ~Light(void);

    void bind(int);
    void unbind(void);

    Vector4 m_position;
    
    Color m_ambientColor;
    Color m_diffuseColor;
    Color m_specularColor;
    
    float m_constantAttenuation;
    float m_linearAttenuation;
    float m_quadraticAttenuation;
    
protected:
    
    int m_bindID;
    
};

#endif
