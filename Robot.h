#ifndef CUBE_ROBOT_H
#define CUBE_ROBOT_H

#include <memory>
#include <unordered_map>

#include "Geode.h"
#include "MatrixTransform.h"

using std::shared_ptr;
using std::make_shared;
using std::make_pair;
using std::unordered_map;

typedef struct BodyPart{
    MatrixTransformPtr scale;
    MatrixTransformPtr rotatation;
    MatrixTransformPtr translation;
}BodyPart;

class Robot : public Geode {

public:

    Robot(GeodePtr head, GeodePtr torso, GeodePtr arms, GeodePtr legs);
    ~Robot();

    void render();
    void build();

protected:

    enum {
        HEAD,
        TORSO,
        LARM,
        RARM,
        LLEG,
        RLEG
    };

    GeodePtr m_head;
    GeodePtr m_torso;
    GeodePtr m_legs;
    GeodePtr m_arms;

    MatrixTransformPtr m_robotScale;
    MatrixTransformPtr m_robotRotation;
    MatrixTransformPtr m_robotTranslatation;
    unordered_map<int, BodyPart> m_bodyParts;

};

#endif