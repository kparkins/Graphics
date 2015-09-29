#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>
#include "Color.h"

class Material {
    
public:
    
    Material(void);
    ~Material(void);
    
    virtual void apply(void);
    
    Color ambientColor;
    Color diffuseColor;
    Color specularColor;
    Color emissionColor;
    
    float shininess;
    
    //A color variable used in Projects 1, 2, and 3
    //This can be removed once materials are implemented
    Color color;
    
};

#endif
