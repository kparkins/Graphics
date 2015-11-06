#include "Robot.h"

Robot::Robot(GeodePtr head, GeodePtr torso, GeodePtr arms, GeodePtr legs) :
        m_head(head),
        m_torso(torso),
        m_arms(arms),
        m_legs(legs),
        m_elapsedTime(0.f) {

    m_robotScale = make_shared<MatrixTransform>();
    m_robotRotation = make_shared<MatrixTransform>();
    m_robotTranslatation = make_shared<MatrixTransform>();

    m_robotTranslatation->addChild(m_robotRotation);
    m_robotRotation->addChild(m_robotScale);
    m_robotScale->m_cull = true;
    m_delta = .05f;

    this->build();
}

Robot::~Robot() {

}

void Robot::update(float dt) {
    if(m_rotX > 1.0472f) {
        m_delta *= -1.f;
        m_rotX = 1.0472f;
    } else if(m_rotX < -1.0472f) {
        m_delta *= -1.f;
        m_rotX = -1.0472f;
    }

    Matrix4 rotX;
    Matrix4 rotZ;
    BodyPart larm = m_bodyParts[LARM];
    BodyPart rarm = m_bodyParts[RARM];
    BodyPart lleg = m_bodyParts[LLEG];
    BodyPart rleg = m_bodyParts[RLEG];

    m_rotX += m_delta;

    rotZ.makeRotateZ(-m_rotZ);
    rotX.makeRotateX(m_rotX);

    larm.rotatation->setTransform(rotZ * rotX);
    rleg.rotatation->setTransform(rotX);

    rotZ.makeRotateZ(m_rotZ);
    rotX.makeRotateX(-m_rotX);
    lleg.rotatation->setTransform(rotX);
    rarm.rotatation->setTransform(rotZ * rotX);

}

void Robot::render() {
    Matrix4 ident;
    m_robotTranslatation->draw(ident);
}

void Robot::build() {
    BodyPart b;
    for(int i = 0; i <= RLEG; ++i) {
        b.scale = make_shared<MatrixTransform>();
        b.rotatation = make_shared<MatrixTransform>();
        b.translation = make_shared<MatrixTransform>();
        b.firstTranslate = make_shared<MatrixTransform>();
        b.translation->addChild(b.rotatation);
        if(i == RLEG || i == LLEG || i == LARM || i == RARM) {
            b.rotatation->addChild(b.firstTranslate);
            b.firstTranslate->addChild(b.scale);
        } else {
            b.rotatation->addChild(b.scale);
        }
        m_bodyParts.insert(make_pair(i, b));
    }

    BodyPart head = m_bodyParts[HEAD];
    BodyPart torso = m_bodyParts[TORSO];
    BodyPart lleg = m_bodyParts[LLEG];
    BodyPart rleg = m_bodyParts[RLEG];
    BodyPart larm = m_bodyParts[LARM];
    BodyPart rarm = m_bodyParts[RARM];

    m_robotTranslatation->addChild(head.translation);
    m_robotTranslatation->addChild(torso.translation);
    m_robotTranslatation->addChild(larm.translation);
    m_robotTranslatation->addChild(rarm.translation);
    m_robotTranslatation->addChild(lleg.translation);
    m_robotTranslatation->addChild(rleg.translation);

    head.scale->addChild(m_head);
    torso.scale->addChild(m_torso);
    larm.scale->addChild(m_arms);
    rarm.scale->addChild(m_arms);
    lleg.scale->addChild(m_legs);
    rleg.scale->addChild(m_legs);

    this->initialState();
}


void Robot::initialState() {
    Matrix4 trans;
    BodyPart head = m_bodyParts[HEAD];
    BodyPart torso = m_bodyParts[TORSO];
    BodyPart lleg = m_bodyParts[LLEG];
    BodyPart rleg = m_bodyParts[RLEG];
    BodyPart larm = m_bodyParts[LARM];
    BodyPart rarm = m_bodyParts[RARM];

    ///////////    Scale    ////////////

    trans.makeScale(1.f);
    head.scale->setTransform(trans);
    head.scale->m_bs = true;
    head.scale->m_boundingSphere.radius = 1.005f;

    trans.makeScale(1.25f, 1.5f, 1.0f);
    torso.scale->setTransform(trans);
    torso.scale->m_bs = true;
    torso.scale->m_boundingSphere.radius = 1.5;

    trans.makeScale(.6f, 1.5f, 1.f);
    larm.scale->setTransform(trans);
    larm.scale->m_bs = true;
    larm.scale->m_boundingSphere.radius = 1.5f;
    rarm.scale->setTransform(trans);
    rarm.scale->m_bs = true;
    rarm.scale->m_boundingSphere.radius = 1.5f;
    lleg.scale->setTransform(trans);
    lleg.scale->m_bs = true;
    lleg.scale->m_boundingSphere.radius = 1.5f;
    rleg.scale->setTransform(trans);
    rleg.scale->m_bs = true;
    rleg.scale->m_boundingSphere.radius = 1.5f;

    ///////////   Rotate   ////////////

    m_rotZ = 0.523599f;
    trans.makeRotateZ(-m_rotZ);
    larm.rotatation->setTransform(trans);

    trans.makeRotateZ(m_rotZ);
    rarm.rotatation->setTransform(trans);

    /////////// Translate ////////////
    trans.makeTranslate(0.f, -.8f, 0.f);
    larm.firstTranslate->setTransform(trans);
    rarm.firstTranslate->setTransform(trans);
    lleg.firstTranslate->setTransform(trans);
    rleg.firstTranslate->setTransform(trans);

    trans.makeTranslate(0.f, 2.f, 0.f);
    head.translation->setTransform(trans);

    trans.makeTranslate(-1.6f, .5f, 0.f);
    larm.translation->setTransform(trans);

    trans.makeTranslate(1.6f, .5f, 0.f);
    rarm.translation->setTransform(trans);

    trans.makeTranslate(-.8f, -1.6f, 0.f);
    lleg.translation->setTransform(trans);

    trans.makeTranslate(.8f, -1.6f, 0.f);
    rleg.translation->setTransform(trans);
    m_boundingSphere.radius = 3.6f;
    m_bs = true;
}
