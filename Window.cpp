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
bool Window::runAnimation = false;

LightPtr Window::m_directionalLight;

GeodePtr Window::m_sphere;
GeodePtr Window::m_cube;
CameraPtr Window::m_camera;
GroupPtr Window::m_scene;
GeodePtr Window::m_robot;
Frustrum Window::frustrum;
MatrixTransformPtr Window::squad1Rot;
MatrixTransformPtr Window::squad1Trans;
MatrixTransformPtr Window::squad2Rot;
MatrixTransformPtr Window::squad2Trans;
MatrixTransformPtr Window::squad2scale;
MatrixTransformPtr Window::squad1scale;
PlatoonPtr Window::squad1;
PlatoonPtr Window::squad2;
Matrix4 Window::worldScale;
float totalCols;


void Window::initialize() {
    m_camera = make_shared<Camera>();
    m_sphere = make_shared<Sphere>(1.f, 15, 15);
    m_cube = make_shared<Cube>(1.f);
    m_scene = make_shared<Group>();
    m_robot = make_shared<Robot>(m_sphere, m_sphere, m_sphere, m_sphere);

    float row1 = 5;
    float col1 = 5;
    float row2 = 5;
    float col2 = 5;
    totalCols = col2 + col1;
    squad1 = make_shared<Platoon>(row1, col1, Vector3(2.5f, 0.f, 3.5f), m_robot);
    squad1Rot = make_shared<MatrixTransform>();
    squad1Trans = make_shared<MatrixTransform>();
    squad1scale = make_shared<MatrixTransform>();
    squad1Trans->addChild(squad1Rot);
    squad1Rot->addChild(squad1scale);
    squad1scale->addChild(squad1);
    m_scene->addChild(squad1Trans);

    squad2 = make_shared<Platoon>(row2, col2, Vector3(-5.f, 0.f, 0.f), m_robot);
    squad2->m_geometry = m_robot;
    squad2->invertXOffset();
    squad2Rot = make_shared<MatrixTransform>();
    squad2Trans = make_shared<MatrixTransform>();
    squad2scale = make_shared<MatrixTransform>();
    squad2Trans->addChild(squad2Rot);
    squad2Rot->addChild(squad2scale);
    squad2scale->addChild(squad2);
    m_scene->addChild(squad2Trans);

    worldScale.identity();

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
    m_robot->update(1.f);
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
    frustrum.aspect = ((double) width) / ((double ) height);
    frustrum.fov = 60.f * M_PI / 180.f;
    frustrum.halfFov = tanf(60.f * M_PI / 180.f * .5f);
    frustrum.nearPlane = 1.f;
    frustrum.farPlane = 1000.f;
    frustrum.nearHeight = frustrum.nearPlane * frustrum.halfFov;
    frustrum.nearWidth = frustrum.nearHeight * frustrum.aspect;
    frustrum.farHeight = frustrum.farPlane * frustrum.halfFov;
    frustrum.farWidth = frustrum.farHeight * frustrum.aspect;
    frustrum.e = m_camera->e;
    frustrum.d = m_camera->d;
    frustrum.up = m_camera->up;
    frustrum.up.normalize();

    frustrum.z = frustrum.e - frustrum.d;
    frustrum.z.normalize();

    frustrum.x = frustrum.up.cross(frustrum.z);
    frustrum.x.normalize();

    frustrum.y = frustrum.z.cross(frustrum.x);
    frustrum.y.normalize();

    frustrum.farCenter = frustrum.e + frustrum.z * frustrum.farPlane;
    frustrum.farTopLeft = frustrum.farCenter + frustrum.y * frustrum.farHeight - frustrum.x * frustrum.farWidth;
    frustrum.farTopRight = frustrum.farCenter + frustrum.y * frustrum.farHeight + frustrum.x * frustrum.farWidth;
    frustrum.farBottomLeft = frustrum.farCenter - frustrum.y * frustrum.farHeight - frustrum.x * frustrum.farWidth;
    frustrum.farBottomRight = frustrum.farCenter - frustrum.y * frustrum.farHeight + frustrum.x * frustrum.farWidth;

    frustrum.nearCenter = frustrum.e - frustrum.z * frustrum.nearPlane;
    frustrum.nearTopLeft = frustrum.nearCenter + frustrum.y * frustrum.nearHeight - frustrum.x * frustrum.nearWidth;
    frustrum.nearTopRight = frustrum.nearCenter + frustrum.y * frustrum.nearHeight + frustrum.x * frustrum.nearWidth;
    frustrum.nearBottomLeft = frustrum.nearCenter - frustrum.y * frustrum.nearHeight - frustrum.x * frustrum.nearWidth;
    frustrum.nearBottomRight = frustrum.nearCenter - frustrum.y * frustrum.nearHeight + frustrum.x * frustrum.nearWidth;

    frustrum.planes[Frustrum::TOP].set(frustrum.nearTopRight, frustrum.nearTopLeft, frustrum.farTopLeft);
    frustrum.planes[Frustrum::BOTTOM].set(frustrum.nearBottomLeft, frustrum.nearBottomRight, frustrum.farBottomRight);
    frustrum.planes[Frustrum::LEFT].set(frustrum.nearTopLeft, frustrum.nearBottomLeft, frustrum.farBottomLeft);
    frustrum.planes[Frustrum::RIGHT].set(frustrum.nearBottomRight, frustrum.nearTopRight, frustrum.farBottomRight);
    frustrum.planes[Frustrum::NEAR].set(frustrum.nearTopLeft, frustrum.nearTopRight, frustrum.nearBottomRight);
    frustrum.planes[Frustrum::FAR].set(frustrum.farTopRight, frustrum.farTopLeft, frustrum.farBottomLeft);
}


static int animSteps;
void Window::runSquadAnim() {
    Matrix4 trans1;
    Matrix4 rot1;
    Matrix4 trans2;
    Matrix4 rot2;
    if(animSteps == 200.f) {
        rot1.makeRotateY(-1.5708f);
        rot2.makeRotateY(-1.5708f);

        squad1->m_rotation->setTransform(squad1->m_rotation->getTransform() * rot1);
        squad2->m_rotation->setTransform(squad2->m_rotation->getTransform() * rot2);

    } else if(animSteps == 400.f) {
        rot1.makeRotateY(-1.5708f);
        rot2.makeRotateY(-1.5708f);

        squad1->m_rotation->setTransform(squad1->m_rotation->getTransform() * rot1);
        squad2->m_rotation->setTransform(squad2->m_rotation->getTransform() * rot2);
    } else if(animSteps == 600.f) {
        rot1.makeRotateY(-1.5708f);
        rot2.makeRotateY(-1.5708f);

        squad1->m_rotation->setTransform(squad1->m_rotation->getTransform() * rot1);
        squad2->m_rotation->setTransform(squad2->m_rotation->getTransform() * rot2);
    } else if(animSteps == 800.f) {
        rot1.makeRotateY(-1.5708f);
        rot2.makeRotateY(-1.5708f);

        squad1->m_rotation->setTransform(squad1->m_rotation->getTransform() * rot1);
        squad2->m_rotation->setTransform(squad2->m_rotation->getTransform() * rot2);
    }

    if(animSteps < 200.f) {
        trans1.makeTranslate(Vector3(0.f, 0.f, .05f));
        trans2.makeTranslate(Vector3(0.f, 0.f, -0.05f));
        squad1Trans->setTransform(squad1Trans->getTransform() * trans1);
        squad2Trans->setTransform(squad2Trans->getTransform() * trans2);
    } else if(animSteps < 400.f) {
        trans1.makeTranslate(Vector3(-.05f, 0.f, 0.f));
        trans2.makeTranslate(Vector3(.05f, 0.f, 0.f));
        squad1Trans->setTransform(squad1Trans->getTransform() * trans1);
        squad2Trans->setTransform(squad2Trans->getTransform() * trans2);
    } else if(animSteps < 600.f) {
        trans1.makeTranslate(Vector3(0.f, 0.f, -.05f));
        trans2.makeTranslate(Vector3(0.f, 0.f, 0.05f));
        squad1Trans->setTransform(squad1Trans->getTransform() * trans1);
        squad2Trans->setTransform(squad2Trans->getTransform() * trans2);
    } else if(animSteps <= 800.f) {
        trans1.makeTranslate(Vector3(.05f, 0.f, 0.f));
        trans2.makeTranslate(Vector3(-.05f, -0.f, 0.f));
        squad1Trans->setTransform(squad1Trans->getTransform() * trans1);
        squad2Trans->setTransform(squad2Trans->getTransform() * trans2);
    } else {
        animSteps = 0.f;
    }
    ++animSteps;
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
    runSquadAnim();

    Matrix4 ident;
    m_scene->draw(worldScale);

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
    Matrix4 trans;
    switch (key) {
        case 'c':
            Globals::enableCulling = !Globals::enableCulling;
            break;
        case 'b':
            Globals::drawBoundingSphere = !Globals::drawBoundingSphere;
            break;
        case 's':
            trans.makeScale(.9f);
            worldScale = worldScale * trans;
           /* squad1scale->setTransform(squad1scale->getTransform() * trans);
            squad2scale->setTransform(squad2scale->getTransform() * trans);
            */
            break;
        case 'S':
            trans.makeScale(1.1f);
            worldScale = worldScale * trans;
            /*squad1scale->setTransform(squad1scale->getTransform() * trans);
            squad2scale->setTransform(squad2scale->getTransform() * trans);
            */
            break;
        default:
            break;
    }
}

void Window::doShit(Matrix4 & trans) {
    m_camera->e = (trans.multiply(m_camera->e));
    m_camera->up = (trans.multiply(m_camera->up));
    m_camera->update();
    reshapeCallback(Window::width, Window::height);
}

void Window::specialKeyCallback(int key, int x, int y) {
    Matrix4 trans;
    switch (key) {
        case GLUT_KEY_UP:
            trans.makeRotateX(.05f);
            doShit(trans);
            break;
        case GLUT_KEY_DOWN:
            trans.makeRotateX(-.05f);
            doShit(trans);
            break;
        case GLUT_KEY_LEFT:
            trans.makeRotateY(.05f);
            doShit(trans);
            break;
        case GLUT_KEY_RIGHT:
            trans.makeRotateY(-.05f);
            doShit(trans);
            break;
        default:
            break;
    }
}

void Window::mouseButtonCallback(int button, int state, int x, int y) {
}

