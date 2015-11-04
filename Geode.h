#ifndef CUBE_GEODE_H
#define CUBE_GEODE_H

#include "Node.h"

class Geode : public Node {

public:

    virtual ~Geode();

    virtual void render() = 0;
    void draw(Matrix4 & c) override;

};

#endif