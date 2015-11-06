#ifndef CUBE_GEODE_H
#define CUBE_GEODE_H

#include "Node.h"
#include "Globals.h"
#include "MaterialFactory.h"


class Geode : public Node {

public:

    Geode();
    virtual ~Geode();

    virtual void render() = 0;
    void draw(Matrix4 & c) override;
    void update(float dt) override;

    Material m_material;
};

typedef shared_ptr<Geode> GeodePtr;

#endif