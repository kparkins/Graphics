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

    Vector4 position;
    
    Color ambientColor;
    Color diffuseColor;
    Color specularColor;
    
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
    
protected:
    
    int bindID;
    
};

#endif
