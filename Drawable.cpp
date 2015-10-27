#include "Drawable.h"
#include "Window.h"

Drawable::Drawable() {
    this->m_toWorld.identity();
    this->m_rotationY = 0.f;
    memset(static_cast<void*>(&m_box), 0, sizeof(m_box));
}

Drawable::~Drawable() {
    //
}

void Drawable::draw(DrawData& data) {
    std::cout << "Warning: draw() is not implemented" << std::endl;
}

void Drawable::update(UpdateData& data) {
    std::cout << "Warning: update() is not implemented" << std::endl;
}

const vector<float>& Drawable::getVertexArray() {
    return this->m_vertexArray;
}

void Drawable::translateToOrigin() {
    std::cout << "Warning: relative to origin not implemented." << std::endl;
}

void Drawable::computeBoundingBox() {
    std::cout << "Warning: compute bounding box not implemented." << std::endl;
}
