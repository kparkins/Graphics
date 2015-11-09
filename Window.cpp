#include "window.h"

void gfx::window::initialize() {
    m_camera = make_shared<camera>();
    m_sphere = make_shared<sphere>(1.f, 15, 15);
    m_cube = make_shared<cube>(1.f);
    m_scene = make_shared<group>();
    m_directlight = make_shared<light>();
    m_pointlight = make_shared<light>();

    m_directlight->position(vec4(0.f, 0.f, 1.f, 0.f));

    m_worldscale.identity();
    m_scene->add(m_cube);
}

void gfx::window::idlecb() {
    frame++;
    time = glutGet(GLUT_ELAPSED_TIME);
    int fps;
    if (time - timebase > 1000) {
        fps = frame * 1000.0 / (time - timebase);
        timebase = time;
        frame = 0;
        std::cout << "fps\t" << fps << std::endl;
    }
    displaycb();
}

void gfx::window::reshapecb(int w, int h) {
    m_width = w;                                                       //Set the window m_width
    m_height = h;                                                      //Set the window m_height
    glViewport(0, 0, w, h);                                          //Set new viewport m_size
    glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
    glLoadIdentity();                                                //Clear the projection matrix by loading the identity
    gluPerspective(60.0, double(m_width)/(double) m_height, 1.0, 1000.0); //Set perspective projection viewing frustum
}

void gfx::window::displaycb() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadMatrixf(m_camera->inverse_matrix().ptr());

    m_directlight->bind(1);
    m_scene->draw(m_worldscale);
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void gfx::window::keycb(unsigned char key, int x, int y) {

}

void gfx::window::specialkeycb(int key, int x, int y) {

}

void gfx::window::mousebuttoncb(int button, int state, int x, int y) {

}

int gfx::window::width() {
    this->m_width;
}

int gfx::window::height() {
    return this->m_height;
}

void gfx::window::width(int w) {
    assert(w > 0);
    this->m_width = w;
}

void gfx::window::height(int h) {
    assert(h > 0);
    this->m_height = h;
}
