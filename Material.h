#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>
#include "Color.h"

class Material {
    
public:
    
    Material(void);
    ~Material(void);
    
    virtual void apply(void);
    
    Color m_ambientColor;
    Color m_diffuseColor;
    Color m_specularColor;
    Color m_emissionColor;
    
    float m_shininess;
    
};

#endif
