#include "Geode.h"

Geode::~Geode() {

}

void Geode::draw(Matrix4 &c) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(c.ptr());
    this->render();
    glPopMatrix();
}

