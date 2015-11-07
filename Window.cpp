#include <iostream>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "window.h"

int gfx::window::width  = 512;   //Set window width in pixels here
int gfx::window::height = 512;   //Set window height in pixels here
int gfx::window::frame = 0;
int gfx::window::timebase = 0;
int gfx::window::time = 0;

gfx::geode_ptr gfx::window::m_sphere;
gfx::geode_ptr gfx::window::m_cube;
gfx::camera_ptr gfx::window::m_camera;
gfx::group_ptr gfx::window::m_scene;
gfx::mat4 gfx::window::world_scale;

void gfx::window::initialize() {
    m_camera = make_shared<camera>();
    m_sphere = make_shared<sphere>(1.f, 15, 15);
    m_cube = make_shared<cube>(1.f);
    m_scene = make_shared<group>();
    world_scale.identity();
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
    m_robot->update(1.f);
    displaycb();
}

void gfx::window::reshapecb(int w, int h) {
    width = w;                                                       //Set the window width
    height = h;                                                      //Set the window height
    glViewport(0, 0, w, h);                                          //Set new viewport m_size
    glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
    glLoadIdentity();                                                //Clear the projection matrix by loading the identity
    gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); //Set perspective projection viewing frustum
}

void gfx::window::displaycb() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadMatrixf(m_camera->inverse_matrix().ptr());

    m_scene->draw(world_scale);

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

