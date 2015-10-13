#include <iostream>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "Cube.h"
#include "Globals.h"
#include "Rasterizer.h"

int Window::width  = 512;   //Set window width in pixels here
int Window::height = 512;   //Set window height in pixels here
int Window::frame = 0;
int Window::timebase = 0;
int Window::time = 0;
bool Window::m_useRasterizer = false;

DrawablePtr Window::m_cube;
DrawablePtr Window::m_sphere;
DrawablePtr Window::m_house;
DrawablePtr Window::m_model;

OBJObjectPtr Window::m_bear;
OBJObjectPtr Window::m_bunny;
OBJObjectPtr Window::m_dragon;

void Window::initialize(void) {
    //Setup the light
    Vector4 lightPos(0.0, 10.0, 15.0, 1.0);
    Globals::light.m_position = lightPos;
    Globals::light.m_quadraticAttenuation = 0.02;

    m_cube = make_shared<Cube>(10.f);
    m_sphere = make_shared<Sphere>(4.f, 100, 10);
    m_house = make_shared<House>();
    m_model = m_cube;
    m_bear = make_shared<OBJObject>();
    m_bunny = make_shared<OBJObject>();
    m_dragon = make_shared<OBJObject>();

    thread bear(&OBJObject::generateMesh, m_bear, "bear.obj");
    thread bunny(&OBJObject::generateMesh, m_bunny, "bunny.obj");
    thread dragon(&OBJObject::generateMesh, m_dragon, "dragon.obj");
    std::this_thread::yield();
    bear.join();
    bunny.join();
    dragon.join();

    m_bear->loadVabo();
    m_bunny->loadVabo();
    m_dragon->loadVabo();

    m_cube->m_rotationY = .005;

    //Initialize cube matrix:
    m_cube->m_toWorld.identity();

    //Setup the cube's m_material properties
    Color color(0x23ff27ff);
    m_cube->m_material.m_color = color;
}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
// This is called at the start of every new "frame" (qualitatively)
void Window::idleCallback() {
    //Set up a static time delta for update calls
    Globals::updateData.m_dt = 1.0/60.0;// 60 fps
    
    Matrix4 rotation;
    rotation.makeRotateY(m_model->m_rotationY);
    m_model->m_toWorld = m_model->m_toWorld * rotation;
    m_model->update(Globals::updateData);
    frame++;
    time = glutGet(GLUT_ELAPSED_TIME);
    int fps;
    if (time - timebase > 1000) {
        fps = frame*1000.0/(time-timebase);
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
    glLoadMatrixf(Globals::camera.getInverseMatrix().ptr());

    //Bind the light to slot 0.  We do this after the camera matrix is loaded so that
    //the light m_position will be treated as world coordiantes
    //(if we didn't the light would move with the camera, why is that?)
    Globals::light.bind(0);

    m_model->draw(Globals::drawData);

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
    Matrix4 matrix;
    switch (key) {
        case 'b':
            if(m_model == m_sphere || m_model == m_cube) {
                m_model = (m_model != m_sphere) ? m_sphere : m_cube;
            }
            break;
        case 'x':
            matrix.makeTranslate(Vector3(-1.f, 0.f, 0.f));
            m_model->m_toWorld = matrix * m_model->m_toWorld;
            break;
        case 'X':
            matrix.makeTranslate(Vector3(1.f, 0.f, 0.f));
            m_model->m_toWorld = matrix * m_model->m_toWorld;
            break;
        case 'y':
            matrix.makeTranslate(Vector3(0.f, -1.f, 0.f));
            m_model->m_toWorld = matrix * m_model->m_toWorld;
            break;
        case 'Y':
            matrix.makeTranslate(Vector3(0.f, 1.f, 0.f));
            m_model->m_toWorld = matrix * m_model->m_toWorld;
            break;
        case 'z':
            matrix.makeTranslate(Vector3(0.f, 0.f, 1.f));
            m_model->m_toWorld = matrix * m_model->m_toWorld;
            break;
        case 'Z':
            matrix.makeTranslate(Vector3(0.f, 0.f, -1.f));
            m_model->m_toWorld = matrix * m_model->m_toWorld;
            break;
        case 'c':
            m_model->m_rotationY *= -1.f;
            break;
        case 'r':
            m_model->m_toWorld.identity();
            break;
        case 's':
            matrix.makeScale(.9f);
            m_model->m_toWorld = m_model->m_toWorld * matrix;
            break;
        case 'S':
            matrix.makeScale(1.1f);
            m_model->m_toWorld = m_model->m_toWorld * matrix;
            break;
        case 'o':
            matrix.makeRotateZ(.1745);
            m_model->m_toWorld = matrix * m_model->m_toWorld;
            break;
        case 'O':
            matrix.makeRotateZ(-.1745);
            m_model->m_toWorld = matrix * m_model->m_toWorld;
            break;
        case 'e':
            if(m_useRasterizer) {
                Rasterizer::enable();
            } else {
                Rasterizer::disable();
            }
            m_useRasterizer = !m_useRasterizer;
        default:
            break;
    }
}


void Window::specialKeyCallback(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_F1:
            glEnable(GL_LIGHTING);
            Globals::camera.reset();
            m_model = m_cube;
            break;
        case GLUT_KEY_F2: {
            glDisable(GL_LIGHTING);
            Vector3 e(0.f, 24.14f, 24.14f);
            Vector3 d(0.f, 0.f, 0.f);
            Vector3 up(0.f, 1.f, 0.0f);
            Globals::camera.set(e, d, up);
            m_model = m_house;
            break;
        }
        case GLUT_KEY_F3: {
            glDisable(GL_LIGHTING);
            Vector3 e(-28.33f, 11.66f, 23.33f);
            Vector3 d(-5.f, 0.f, 0.f);
            Vector3 up(0.f, 1.f, -.5f);
            Globals::camera.set(e, d, up);
            m_model = m_house;
            break;
        }
        case GLUT_KEY_F4:
            glEnable(GL_LIGHTING);
            Globals::camera.reset();
            m_model = m_bunny;
            break;
        case GLUT_KEY_F5:
            glEnable(GL_LIGHTING);
            Globals::camera.reset();
            m_model = m_dragon;
            break;
        case GLUT_KEY_F6:
            glEnable(GL_LIGHTING);
            Globals::camera.reset();
            m_model = m_bear;
            break;
        case GLUT_KEY_F7:
            break;
        default:
            break;
    }
}
