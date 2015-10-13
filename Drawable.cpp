#include "Drawable.h"
#include "Window.h"

Drawable::Drawable() {
    this->m_toWorld.identity();
    this->m_rotationY = 0.f;
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
