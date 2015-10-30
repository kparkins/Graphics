//
// Created by Kyle J Parkinson on 10/29/15.
//

#ifndef CUBE_MATERIALFACTORY_H
#define CUBE_MATERIALFACTORY_H

#include "Material.h"
#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

class MaterialFactory {

public:

    MaterialFactory();
    ~MaterialFactory();

    MaterialFactory& setAmbient(Color c);
    MaterialFactory& setAmbient(float r, float g, float b, float a);
    MaterialFactory& setDiffuse(Color c);
    MaterialFactory& setDiffuse(float r, float g, float b, float a);
    MaterialFactory& setSpecular(Color c);
    MaterialFactory& setSpecular(float r, float g, float b, float a);
    MaterialFactory& setEmissive(Color c);
    MaterialFactory& setEmissive(float r, float g, float b, float a);
    MaterialFactory& setShinniness(float s);

    Material make(const string & material);
    Material build();

    void clear();
    void save(const string & name);
    bool load(const string & material);

private:

    Material m_material;
    unordered_map<string, Material> m_materialMap;

};


#endif //CUBE_MATERIALFACTORY_H
