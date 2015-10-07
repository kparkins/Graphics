#include "House.h"

House::House() {
}

House::~House() {

}

void House::draw(DrawData & data) {

    m_material.apply();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(m_toWorld.ptr());

    int index = 0;
    glBegin(GL_TRIANGLES);
    for(int i = 0; i < 60; ++i) {
        index = indices[i] * 3;
        glColor3f(colors[index], colors[index + 1], colors[index + 2]);
        glVertex3f(vertices[index], vertices[index + 1], vertices[index + 2]);
    }
    glEnd();

    glPopMatrix();
}

void House::update(UpdateData & data) {

}

