#include "Robot.h"

Robot::Robot(GeodePtr head, GeodePtr torso, GeodePtr arms, GeodePtr legs) :
        m_head(head),
        m_torso(torso),
        m_arms(arms),
        m_legs(legs)
{
    m_robotScale = make_shared<MatrixTransform>();
    m_robotRotation = make_shared<MatrixTransform>();
    m_robotTranslatation = make_shared<MatrixTransform>();

    m_robotTranslatation->addChild(m_robotRotation);
    m_robotRotation->addChild(m_robotScale);

    this->build();
}

Robot::~Robot() {

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
        b.translation->addChild(b.rotatation);
        b.rotatation->addChild(b.scale);
        m_bodyParts.insert(make_pair(i, b));
    }

    BodyPart head = m_bodyParts[HEAD];
    BodyPart torso = m_bodyParts[TORSO];
    BodyPart lleg = m_bodyParts[LLEG];
    BodyPart rleg = m_bodyParts[RLEG];
    BodyPart larm = m_bodyParts[LARM];
    BodyPart rarm = m_bodyParts[RARM];

    Matrix4 trans;

    ///////////    Scale    ////////////
    trans.makeScale(1.f);
    head.scale->setTransform(trans);

    trans.makeScale(1.25f, 1.5f, 1.0f);
    torso.scale->setTransform(trans);

    trans.makeScale(.6f, 1.5f, 1.f);
    larm.scale->setTransform(trans);
    rarm.scale->setTransform(trans);
    lleg.scale->setTransform(trans);
    rleg.scale->setTransform(trans);

    ///////////   Rotate   ////////////

    trans.makeRotateZ(-0.523599f);
    larm.rotatation->setTransform(trans);

    trans.makeRotateZ(0.5f);
    rarm.rotatation->setTransform(trans);

    /////////// Translate ////////////

    trans.makeTranslate(0.f, 2.f, 0.f);
    head.translation->setTransform(trans);

    trans.makeTranslate(-1.8f, -.30f, 0.f);
    larm.translation->setTransform(trans);

    trans.makeTranslate(1.8f, -.30f, 0.f);
    rarm.translation->setTransform(trans);

    trans.makeTranslate(-.8f, -2.f, 0.f);
    lleg.translation->setTransform(trans);

    trans.makeTranslate(.8f, -2.f, 0.f);
    rleg.translation->setTransform(trans);

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

}
