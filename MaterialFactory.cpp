//
// Created by Kyle J Parkinson on 10/29/15.
//

#include "MaterialFactory.h"

MaterialFactory::MaterialFactory() {

    m_materialMap["gold"] =
            setAmbient(.24725f, .1995f, .0745f, 1.f)
           .setDiffuse(.75164f, .60648f, .22648f, 1.f)
           .setSpecular(.628281f, .555802f, .366065f, 1.f)
           .setShinniness(51.2f)
           .build();

    m_materialMap["polished gold"] =
            setAmbient(.24725f, 0.2245f, 0.0645f, 1.0f)
           .setDiffuse(0.34615f, 0.3143f, 0.0903f, 1.0f)
           .setSpecular(0.797357f, 0.723991f, 0.208006f, 1.0f)
           .setShinniness(83.2f)
           .build();

    m_materialMap["brass"] =
            setAmbient(0.329412f, 0.223529f, 0.027451f,1.0f)
           .setDiffuse(0.780392f, 0.568627f, 0.113725f, 1.0f)
           .setSpecular(0.992157f, 0.941176f, 0.807843f, 1.0f)
           .setShinniness(27.8974f)
           .build();

    m_materialMap["red rubber"] =
            setAmbient(0.05f, 0.f, 0.f, 1.f)
           .setDiffuse(0.5f, 0.4f, 0.4f, 1.f)
           .setSpecular(0.7f, 0.04f, 0.04f, 1.f)
           .setShinniness(10.f)
           .build();

    m_materialMap["shiny tin"] =
            setAmbient(0.105882f, 0.058824f, 0.113725f, 1.f)
           .setDiffuse(.427451f, .470588f, 0.541176f, 1.f)
           .setSpecular(.33333f, 0.33333f, .521569f, 1.f)
           .setShinniness(127.f)
           .build();

    m_materialMap["jade"] =
            setAmbient(0.135f, 0.2225f, 0.1575f, 0.95f)
           .setDiffuse(0.54f, 0.89f, 0.63f, 0.95f)
           .setSpecular(0.316228f, 0.316228f, 0.316228f, 0.95f)
           .setShinniness(76.8f)
           .build();

    m_materialMap["some color"] =
            setAmbient(0.0f,0.1f,0.06f ,1.0f)
           .setDiffuse(0.0f,0.3f,0.9f,1.0f)
           .setSpecular(0.f,0.f,0.f,1.0f)
           .setShinniness(32.f)
           .build();

    m_materialMap["flat yellow"] =
            setAmbient(1.f, 1.f, .5f, 1.f)
           .setDiffuse(1.f, 1.f, .5f, 1.f)
           .setSpecular(1.f, 1.f, .5f, 1.f)
           .setShinniness(0.f)
           .build();

    m_materialMap["white"] =
            setAmbient(Color::white())
           .setDiffuse(Color::white())
           .setSpecular(Color::white())
           .setShinniness(0.f)
           .build();
}

MaterialFactory::~MaterialFactory() {

}

MaterialFactory& MaterialFactory::setAmbient(Color c) {
    m_material.m_ambientColor = c;
    return *this;
}

MaterialFactory& MaterialFactory::setAmbient(float r, float g, float b, float a) {
    return this->setAmbient(Color(r, g, b, a));
}

MaterialFactory& MaterialFactory::setDiffuse(Color c) {
    m_material.m_diffuseColor = c;
    return  *this;
}

MaterialFactory& MaterialFactory::setDiffuse(float r, float g, float b, float a) {
    return this->setDiffuse(Color(r, g, b, a));
}

MaterialFactory& MaterialFactory::setSpecular(Color c) {
    m_material.m_specularColor = c;
    return *this;
}

MaterialFactory& MaterialFactory::setSpecular(float r, float g, float b, float a) {
    return this->setSpecular(Color(r, g, b, a));
}

MaterialFactory& MaterialFactory::setEmissive(Color c) {
    m_material.m_emissionColor = c;
    return *this;
}

MaterialFactory& MaterialFactory::setEmissive(float r, float g, float b, float a) {
    return this->setEmissive(Color(r, g, b, a));
}

MaterialFactory& MaterialFactory::setShinniness(float s) {
    m_material.m_shininess = s;
    return *this;
}

Material MaterialFactory::make(const string & material) {
    auto item = m_materialMap.find(material);
    if(item != m_materialMap.end()) {
        return item->second;
    }
    return Material();
}

Material MaterialFactory::build() {
    return this->m_material;
}

void MaterialFactory::clear() {
    m_material = Material();
}

void MaterialFactory::save(const string & name) {
    m_materialMap[name] = m_material;
}

bool MaterialFactory::load(const string & material) {
    auto item = m_materialMap.find(material);
    if(item != m_materialMap.end()) {
        m_material = item->second;
        return true;
    }
    return false;
}
