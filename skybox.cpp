#include "skybox.h"

float gfx::skybox::m_vertices[72] = {
        //left
        -.5f, .5f, .5f,
        -.5f, -.5f, .5f,
        -.5f, -.5f, -.5f,
        -.5f, .5f, -.5f,

        //front
        -.5f, .5f, -.5f,
        -.5f, -.5f, -.5f,
        .5f, -.5f, -.5f,
        .5f, .5f, -.5f,

        //right
        .5f, .5f, -.5f,
        .5f, -.5f, -.5f,
        .5f, -.5f, .5f,
        .5f, .5f, .5f,

        //back
        .5f, .5f, .5f,
        .5f, -.5f, .5f,
        -.5f, -.5f, .5f,
        -.5f, .5f, .5f,

        //top
        -.5f, .5f, -.5f,
        .5f, .5f, -.5f,
        .5f, .5f, .5f,
        -.5f, .5f, .5f,

        //bottom
        -.5f, -.5f, -.5f,
        -.5f, -.5f, .5f,
        .5f -5.f, .5f,
        .5f, -.5f, -.5f

};

float gfx::skybox::m_texcoords[48] = {
        //left
        0.f, 1.f,
        1.f, 1.f,
        1.f, 0.f,
        0.f, 0.f,

        //front
        0.f, 1.f,
        1.f, 1.f,
        1.f, 0.f,
        0.f, 0.f,

        //right
        0.f, 1.f,
        1.f, 1.f,
        1.f, 0.f,
        0.f, 0.f,

        //back
        0.f, 1.f,
        1.f, 1.f,
        1.f, 0.f,
        0.f, 0.f,

        //top
        0.f, 1.f,
        1.f, 1.f,
        1.f, 0.f,
        0.f, 0.f,

        //bottom
        0.f, 0.f,
        0.f, 1.f,
        1.f, 1.f,
        1.f, 0.f,
};

gfx::skybox::skybox() {

}

gfx::skybox::~skybox() {

}

void gfx::skybox::draw(mat4 & c) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(c.ptr());
    glEnable(GL_TEXTURE_2D);
    float halfSize = .5f;

    // left
    m_sides[LEFT]->bind();
    glBegin(GL_QUADS);
    glNormal3f(1.f, 0.f, 0.f);
    glTexCoord2f(1, 0); glVertex3f(-halfSize, halfSize, halfSize);
    glTexCoord2f(1, 1); glVertex3f(-halfSize, -halfSize, halfSize);
    glTexCoord2f(0, 1); glVertex3f(-halfSize, -halfSize, -halfSize);
    glTexCoord2f(0, 0); glVertex3f(-halfSize, halfSize, -halfSize);
    glEnd();
    m_sides[LEFT]->unbind();

    //front
    m_sides[FRONT]->bind();
    glBegin(GL_QUADS);
    glNormal3f(0.f, 0.f, 1.f);
    glTexCoord2f(1, 0); glVertex3f(-halfSize, halfSize, -halfSize);
    glTexCoord2f(1, 1); glVertex3f(-halfSize, -halfSize, -halfSize);
    glTexCoord2f(0, 1); glVertex3f(halfSize, -halfSize, -halfSize);
    glTexCoord2f(0, 0); glVertex3f(halfSize, halfSize, -halfSize);
    glEnd();
    m_sides[FRONT]->unbind();

    // Draw right
    m_sides[RIGHT]->bind();
    glBegin(GL_QUADS);
    glNormal3f(-1.f, 0.f, 0.f);
    glTexCoord2f(1, 0); glVertex3f(halfSize, halfSize, -halfSize);
    glTexCoord2f(1, 1); glVertex3f(halfSize, -halfSize, -halfSize);
    glTexCoord2f(0, 1); glVertex3f(halfSize, -halfSize, halfSize);
    glTexCoord2f(0, 0); glVertex3f(halfSize, halfSize, halfSize);
    glEnd();
    m_sides[RIGHT]->unbind();

    // Draw back face:
    m_sides[BACK]->bind();
    glBegin(GL_QUADS);
    glNormal3f(0.f, 0.f, -1.f);
    glTexCoord2f(1, 0); glVertex3f(halfSize, halfSize, halfSize);
    glTexCoord2f(1, 1); glVertex3f(halfSize, -halfSize, halfSize);
    glTexCoord2f(0, 1); glVertex3f(-halfSize, -halfSize, halfSize);
    glTexCoord2f(0, 0); glVertex3f(-halfSize, halfSize, halfSize);
    glEnd();
    m_sides[BACK]->unbind();

    // draw top
    m_sides[TOP]->bind();
    glBegin(GL_QUADS);
    glNormal3f(0.f, -1.f, 0.f);
    glTexCoord2f(1, 0); glVertex3f(-halfSize, halfSize, -halfSize);
    glTexCoord2f(1, 1); glVertex3f(halfSize, halfSize, -halfSize);
    glTexCoord2f(0, 1); glVertex3f(halfSize, halfSize, halfSize);
    glTexCoord2f(0, 0); glVertex3f(-halfSize, halfSize, halfSize);
    glEnd();
    m_sides[TOP]->unbind();

    // draw bottom
    m_sides[BOTTOM]->bind();
    glBegin(GL_QUADS);
    glNormal3f(0.f, 1.f, 0.f);
    glTexCoord2f(1, 1); glVertex3f(-halfSize, -halfSize, -halfSize);
    glTexCoord2f(0, 1); glVertex3f(-halfSize, -halfSize, halfSize);
    glTexCoord2f(0, 0); glVertex3f(halfSize, -halfSize, halfSize);
    glTexCoord2f(1, 0); glVertex3f(halfSize, -halfSize, -halfSize);
    glEnd();
    m_sides[BOTTOM]->unbind();


    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void gfx::skybox::sides(const vector<texture_ptr> & sides) {
    if(sides.size() != 6) {
        return;
    }
    m_sides.clear();
    m_sides.resize(6);
    m_sides[LEFT] = sides[LEFT];
    m_sides[FRONT] = sides[FRONT];
    m_sides[RIGHT] = sides[RIGHT];
    m_sides[BACK] = sides[BACK];
    m_sides[TOP] = sides[TOP];
    m_sides[BOTTOM] = sides[BOTTOM];
}

void gfx::skybox::load(const vector<string> & images) {
    if(images.size() != 6) {
        return;
    }
    m_sides.resize(6);
    m_sides[LEFT] = make_shared<texture>(images[LEFT].c_str());
    m_sides[FRONT] = make_shared<texture>(images[FRONT].c_str());
    m_sides[RIGHT] = make_shared<texture>(images[RIGHT].c_str());
    m_sides[BACK] = make_shared<texture>(images[BACK].c_str());
    m_sides[TOP] = make_shared<texture>(images[TOP].c_str());
    m_sides[BOTTOM] = make_shared<texture>(images[BOTTOM].c_str());
}