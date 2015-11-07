//
// Created by Kyle J Parkinson on 10/29/15.
//

#include "material_factory.h"

gfx::material_factory::material_factory() {

    ambient(.24725f, .1995f, .0745f, 1.f)
   .diffuse(.75164f, .60648f, .22648f, 1.f)
   .specular(.628281f, .555802f, .366065f, 1.f)
   .shinniness(51.2f)
   .save("gold");

    ambient(.24725f, 0.2245f, 0.0645f, 1.0f)
   .diffuse(0.34615f, 0.3143f, 0.0903f, 1.0f)
   .specular(0.797357f, 0.723991f, 0.208006f, 1.0f)
   .shinniness(83.2f)
   .save("polished gold");

    ambient(0.329412f, 0.223529f, 0.027451f,1.0f)
   .diffuse(0.780392f, 0.568627f, 0.113725f, 1.0f)
   .specular(0.992157f, 0.941176f, 0.807843f, 1.0f)
   .shinniness(27.8974f)
   .save("brass");

    ambient(0.05f, 0.f, 0.f, 1.f)
   .diffuse(0.5f, 0.4f, 0.4f, 1.f)
   .specular(0.7f, 0.04f, 0.04f, 1.f)
   .shinniness(10.f)
   .save("red rubber");

    ambient(0.105882f, 0.058824f, 0.113725f, 1.f)
   .diffuse(.427451f, .470588f, 0.541176f, 1.f)
   .specular(.33333f, 0.33333f, .521569f, 1.f)
   .shinniness(127.f)
   .save("shiny tin");

    ambient(0.135f, 0.2225f, 0.1575f, 0.95f)
   .diffuse(0.54f, 0.89f, 0.63f, 0.95f)
   .specular(0.316228f, 0.316228f, 0.316228f, 0.95f)
   .shinniness(76.8f)
   .save("jade");

    ambient(0.0f,0.1f,0.06f ,1.0f)
   .diffuse(0.0f,0.3f,0.9f,1.0f)
   .specular(0.f,0.f,0.f,1.0f)
   .shinniness(32.f)
   .save("some color");

    ambient(1.f, 1.f, .5f, 1.f)
   .diffuse(1.f, 1.f, .5f, 1.f)
   .specular(1.f, 1.f, .5f, 1.f)
   .shinniness(0.f)
   .save("flat yellow");

    ambient(color::color())
   .diffuse(color::color())
   .specular(color::color())
   .shinniness(0.f)
   .save("white");
}

gfx::material_factory::~material_factory() {

}

material gfx::material_factory::get(const string &material) {
    static material_factory factory;
    return factory.make(material);
}

material_factory& gfx::material_factory::ambient(color c) {
    m_material.ambient = c;
    return *this;
}

material_factory& gfx::material_factory::ambient(float r, float g, float b, float a) {
    return this->ambient(color(r, g, b, a));
}

material_factory& gfx::material_factory::diffuse(color c) {
    m_material.diffuse = c;
    return  *this;
}

material_factory& gfx::material_factory::diffuse(float r, float g, float b, float a) {
    return this->diffuse(color(r, g, b, a));
}

material_factory &gfx::material_factory::specular(color c) {
    m_material.specular = c;
    return *this;
}

material_factory &gfx::material_factory::specular(float r, float g, float b, float a) {
    return this->specular(color(r, g, b, a));
}

material_factory &gfx::material_factory::emissive(color c) {
    m_material.emissive = c;
    return *this;
}

material_factory &gfx::material_factory::emissive(float r, float g, float b, float a) {
    return this->emissive(color(r, g, b, a));
}

material_factory &gfx::material_factory::shinniness(float s) {
    m_material.shininess = s;
    return *this;
}

material gfx::material_factory::make(const string & material) {
    auto item = m_materials.find(material);
    if(item != m_materials.end()) {
        return item->second;
    }
    return gfx::material();
}

material gfx::material_factory::build() {
    return this->m_material;
}

void gfx::material_factory::clear() {
    m_material = material();
}

void gfx::material_factory::save(const string & name) {
    m_materials[name] = m_material;
}

bool gfx::material_factory::load(const string & material) {
    auto item = m_materials.find(material);
    if(item != m_materials.end()) {
        m_material = item->second;
        return true;
    }
    return false;
}
