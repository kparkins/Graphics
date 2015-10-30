#ifndef LIGHT_H
#define LIGHT_H

#include "Matrix4.h"
#include "Vector4.h"
#include "Color.h"
#include "Drawable.h"
#include "Vector3.h"
#include "MaterialFactory.h"

#include <vector>

class Light {
 
public:
    
    Light();
    virtual ~Light();

    void bind(int);
    void unbind(void);


    Vector4 getPosition();
    DrawablePtr getModel();
    float getConstantAttenuation();
    float getLinearAttenuation();
    float getQuadraticAttentuation();
    float getSpotAngle();
    float getSpotExponent();

    void setConstantAttenuation(float c);
    void setLinearAttenuation(float c);
    void setQuadraticAttentuation(float c);

    void debugDraw();
    void setPosition(const Vector4 & pos);
    void setSpotAngle(float angle);
    void setSpotDirection(const Vector3 & lookAt);
    void setSpotExponent(float exp);
    void setDirectional(bool on);

protected:

    Color m_ambientColor;
    Color m_diffuseColor;
    Color m_specularColor;

    float m_constantAttenuation;
    float m_linearAttenuation;
    float m_quadraticAttenuation;

    bool m_directional;
    float m_spotExponent;
    float m_spotAngle;
    Vector3 m_spotDirection;
    Vector4 m_position;
    DrawablePtr m_model;
    int m_bindID;

};

typedef std::shared_ptr<Light> LightPtr;

#endif
