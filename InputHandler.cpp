#include "InputHandler.h"

InputHandler::InputHandler() {
    m_keyMap['b'] = std::bind(&InputHandler::toggleShowSphere, this, _1);
    m_keyMap['c'] = std::bind(&InputHandler::toggleSpin, this, _1);
    m_keyMap['x'] = std::bind(&InputHandler::translateNegativeX, this, _1);
    m_keyMap['X'] = std::bind(&InputHandler::translatePositiveX, this, _1);
    m_keyMap['y'] = std::bind(&InputHandler::translateNegativeY, this, _1);
    m_keyMap['Y'] = std::bind(&InputHandler::translatePositiveY, this, _1);
    m_keyMap['z'] = std::bind(&InputHandler::translatePositiveZ, this, _1);
    m_keyMap['Z'] = std::bind(&InputHandler::translateNegativeZ, this, _1);
    m_keyMap['r'] = std::bind(&InputHandler::reset, this, _1);
    m_keyMap['s'] = std::bind(&InputHandler::scaleDown, this, _1);
    m_keyMap['S'] = std::bind(&InputHandler::scaleUp, this, _1);
    m_keyMap['o'] = std::bind(&InputHandler::orbitCounterZ, this, _1);
    m_keyMap['O'] = std::bind(&InputHandler::orbitClockwiseZ, this, _1);
}

InputHandler::~InputHandler() {

}

void InputHandler::handle(char key, InputData data) {
    auto it = m_keyMap.find(key);
    if (it != m_keyMap.end()) {
        it->second(data);
    }
}

void InputHandler::toggleSpin(InputData input) {
    Globals::spinValue *= -1.f;
}

void InputHandler::toggleShowSphere(InputData input) {
    Globals::useSphere = !Globals::useSphere;
}

void InputHandler::translatePositiveX(InputData input) {
    Globals::cube.translate(Vector3(1.f, 0.f, 0.f));
}

void InputHandler::translateNegativeX(InputData input) {
    Globals::cube.translate(Vector3(-1.f, 0.f, 0.f));
}

void InputHandler::translatePositiveY(InputData input) {
    Globals::cube.translate(Vector3(0.f, 1.f, 0.f));
}

void InputHandler::translateNegativeY(InputData input) {
    Globals::cube.translate(Vector3(0.f, -1.f, 0.f));
}

void InputHandler::translatePositiveZ(InputData input) {
    Globals::cube.translate(Vector3(0.f, 0.f, 1.f));
}

void InputHandler::translateNegativeZ(InputData input) {
    Globals::cube.translate(Vector3(0.f, 0.f, -1.f));
}

void InputHandler::reset(InputData input) {
    Globals::cube.m_toWorld.identity();
}

void InputHandler::scaleUp(InputData input) {
    Globals::cube.scale(1.2f);
}

void InputHandler::scaleDown(InputData input) {
    Globals::cube.scale(.9f);
}

void InputHandler::orbitCounterZ(InputData input) {
    Globals::cube.orbitZ(.1745f);
}

void InputHandler::orbitClockwiseZ(InputData input) {
    Globals::cube.orbitZ(-.1745f);
}
