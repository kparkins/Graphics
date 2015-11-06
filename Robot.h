#ifndef CUBE_ROBOT_H
#define CUBE_ROBOT_H

#include <memory>
#include <unordered_map>

#include "Geode.h"
#include "Globals.h"
#include "MatrixTransform.h"

using std::shared_ptr;
using std::make_shared;
using std::make_pair;
using std::unordered_map;

typedef struct BodyPart{
    MatrixTransformPtr scale;
    MatrixTransformPtr firstTranslate;
    MatrixTransformPtr rotatation;
    MatrixTransformPtr translation;
}BodyPart;

class Robot : public Group {

public:

    Robot(GeodePtr head, GeodePtr torso, GeodePtr arms, GeodePtr legs);
    ~Robot();

    void update(float dt);
    void build();

    enum {
        HEAD,
        TORSO,
        LARM,
        RARM,
        LLEG,
        RLEG
    };

    void initialState();

    float m_elapsedTime;

    GeodePtr m_head;
    GeodePtr m_torso;
    GeodePtr m_legs;
    GeodePtr m_arms;

    float m_rotZ;
    float m_rotX;
    float m_delta;

    unordered_map<int, BodyPart> m_bodyParts;

};

#endif