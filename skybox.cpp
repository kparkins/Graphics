#include "skybox.h"

gfx::skybox::skybox() {

}

gfx::skybox::~skybox() {

}

void gfx::skybox::draw(mat4 & c) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(c.ptr());

    GLboolean lighting;
    glGetBooleanv(GL_LIGHTING, &lighting);
    glDisable(GL_LIGHTING);
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

    if(lighting) {
        glEnable(GL_LIGHTING);
    }

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