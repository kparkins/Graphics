#include <iostream>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"

int Window::width  = 512;   //Set window width in pixels here
int Window::height = 512;   //Set window height in pixels here
int Window::frame = 0;
int Window::timebase = 0;
int Window::time = 0;

LightPtr Window::m_directionalLight;

GeodePtr Window::m_sphere;
CameraPtr Window::m_camera;

void Window::initialize() {
    m_camera = make_shared<Camera>();
    m_sphere = make_shared<Sphere>(5.f, 3000, 3000);

    m_directionalLight = make_shared<Light>();
    m_directionalLight->setPosition(Vector4(0.f, 0.f, 1.f, 0.f));
}


//----------------------------------------------------------------------------
// Callback method called when system is idle.
// This is called at the start of every new "frame" (qualitatively)
void Window::idleCallback() {
    frame++;
    time = glutGet(GLUT_ELAPSED_TIME);
    int fps;
    if (time - timebase > 1000) {
        fps = frame * 1000.0 / (time - timebase);
        timebase = time;
        frame = 0;
        std::cout << "fps\t" << fps << std::endl;
    }
    //Call the display routine to draw the cube
    displayCallback();
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h) {
    width = w;                                                       //Set the window width
    height = h;                                                      //Set the window height
    glViewport(0, 0, w, h);                                          //Set new viewport m_size
    glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
    glLoadIdentity();                                                //Clear the projection matrix by loading the identity
    gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); //Set perspective projection viewing frustum
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback() {
    //Clear m_color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Set the OpenGL matrix mode to ModelView
    glMatrixMode(GL_MODELVIEW);
    
    //Push a matrix save point
    //This will save a copy of the current matrix so that we can
    //make changes to it and 'pop' those changes off later.
    glPushMatrix();

    //Replace the current top of the matrix stack with the inverse camera matrix
    //This will convert all world coordiantes into camera coordiantes
    glLoadMatrixf(m_camera->getInverseMatrix().ptr());

    //Bind the light to slot 0.  We do this after the camera matrix is loaded so that
    //the light m_position will be treated as world coordiantes
    //(if we didn't the light would move with the camera, why is that?)

    m_directionalLight->bind(1);
    Matrix4 ident;
    ident.identity();
    m_sphere->draw(ident);

    //Pop off the changes we made to the matrix stack this frame
    glPopMatrix();
    
    //Tell OpenGL to clear any outstanding commands in its command buffer
    //This will make sure that all of our commands are fully executed before
    //we swap buffers and show the user the freshly drawn frame
    glFlush();

    //Swap the off-screen buffer (the one we just drew to) with the on-screen buffer
    glutSwapBuffers();
}

void Window::keyCallback(unsigned char key, int x, int y) {

}

void Window::specialKeyCallback(int key, int x, int y) {

}

void Window::mouseButtonCallback(int button, int state, int x, int y) {

}

