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
    
    //A m_color variable used in Projects 1, 2, and 3
    //This can be removed once materials are implemented
    Color m_color;
    
};

#endif
