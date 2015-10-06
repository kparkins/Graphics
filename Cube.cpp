#include "Cube.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

Cube::Cube(float size) : Drawable() {
    this->m_size = size;
}

Cube::~Cube() {
    //Delete any dynamically allocated memory/objects here
}


void Cube::draw(DrawData & data) {
    float halfSize = m_size / 2.0;
    
    //Apply the m_material properties
    //From here forward anything drawn will be drawn with this m_material
    m_material.apply();
    
    //Set the OpenGL Matrix mode to ModelView (used when drawing geometry)
    glMatrixMode(GL_MODELVIEW);
    
    //Push a save state onto the matrix stack, and multiply in the m_toWorld matrix
    glPushMatrix();
    glMultMatrixf(m_toWorld.ptr());
    
    //Make cube!
    //Note: The glBegin, and glEnd should always be as close to the glNormal/glVertex calls as possible
    //These are special calls that 'freeze' many internal states of OpenGL.
    //Once the glBegin state is active many of the calls made to OpenGL (like glMultMatrixf) will be IGNORED!
    //As a good habit, only call glBegin just before you need to draw, and call end just after you finish
    glBegin(GL_QUADS);
    
    // Draw front face:
    glNormal3f(0.f, 0.f, 1.f);
    glVertex3f(-halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize, -halfSize,  halfSize);
    glVertex3f(-halfSize, -halfSize,  halfSize);
    
    // Draw left side:
    glNormal3f(-1.f, 0.f, 0.f);
    glVertex3f(-halfSize,  halfSize,  halfSize);
    glVertex3f(-halfSize,  halfSize, -halfSize);
    glVertex3f(-halfSize, -halfSize, -halfSize);
    glVertex3f(-halfSize, -halfSize,  halfSize);
    
    // Draw right side:
    glNormal3f(1.f, 0.f, 0.f);
    glVertex3f( halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize,  halfSize);
    
    // Draw back face:
    glNormal3f(0.f, 0.f, -1.f);
    glVertex3f(-halfSize,  halfSize, -halfSize);
    glVertex3f( halfSize,  halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize, -halfSize);
    glVertex3f(-halfSize, -halfSize, -halfSize);
    
    // Draw top side:
    glNormal3f(0.f, 1.f, 0.f);
    glVertex3f(-halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize, -halfSize);
    glVertex3f(-halfSize,  halfSize, -halfSize);
    
    // Draw bottom side:
    glNormal3f(0.f, -1.f, 0.f);
    glVertex3f(-halfSize, -halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize,  halfSize);
    glVertex3f(-halfSize, -halfSize,  halfSize);
    
    glEnd();
    
    //The above glBegin, glEnd, glNormal and glVertex calls can be replaced with a glut convenience function
    //glutSolidCube(m_size);
    
    //Pop the save state off the matrix stack
    //This will undo the multiply we did earlier
    glPopMatrix();
}


void Cube::update(UpdateData& data) {
    //
}

void Cube::spin(float radians) {
    Matrix4 rotation;
    rotation.makeRotateY(radians);
    m_toWorld = m_toWorld * rotation;
}


void Cube::orbitY(float radians) {
    Matrix4 rot;
    rot.makeRotateY(radians);
    m_toWorld = rot * m_toWorld;
}
void Cube::orbitX(float radians) {
    Matrix4 rot;
    rot.makeRotateX(radians);
    m_toWorld = rot * m_toWorld;
}

void Cube::orbitZ(float radians) {
    Matrix4 rot;
    rot.makeRotateZ(radians);
    m_toWorld = rot * m_toWorld;
}

void Cube::scale(float value) {
    Matrix4 mat;
    mat.makeScale(value);
    m_toWorld = m_toWorld * mat;
}

#if defined(__GNUC__) | defined(_clang_)
void Cube::translate(Vector3 translate) {
    Matrix4 trans;
    trans.makeTranslate(translate);
    m_toWorld = trans * m_toWorld;
}
#elif defined(_MSC_VER)
void Cube::translate(Vector3 & translate) {
    Matrix4 trans;
    trans.makeTranslate(translate);
    m_toWorld = trans * m_toWorld;
}
#endif
