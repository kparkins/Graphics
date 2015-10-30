#include <iostream>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "Globals.h"

int Window::width  = 512;   //Set window width in pixels here
int Window::height = 512;   //Set window height in pixels here
int Window::frame = 0;
int Window::timebase = 0;
int Window::time = 0;
bool Window::m_leftButton = false;
bool Window::m_rightButton = false;
bool Window::m_shift = false;
Vector3 Window::prev = Vector3(0.f, 0.f, 1.f);

LightPtr Window::m_directionalLight;
LightPtr Window::m_pointLight;
LightPtr Window::m_spotLight;
LightPtr Window::m_light;

DrawablePtr Window::m_sphere;
DrawablePtr Window::m_model;

OBJObjectPtr Window::m_bear;
OBJObjectPtr Window::m_bunny;
OBJObjectPtr Window::m_dragon;

void Window::initialize(void) {
    MaterialFactory materialFactory;
    //Setup the light
    Vector4 lightPos(0.0, 10.0, 15.0, 1.0);
    Globals::light.setPosition(lightPos);
    Globals::light.setQuadraticAttentuation(.02f);

    m_sphere = make_shared<Sphere>(10.f, 3000, 3000);
    m_bear = make_shared<OBJObject>();
    m_bunny = make_shared<OBJObject>();
    m_dragon = make_shared<OBJObject>();
    m_model = m_sphere;

    m_directionalLight = make_shared<Light>();
    m_pointLight = make_shared<Light>();
    m_spotLight = make_shared<Light>();
    m_light = nullptr;

    m_directionalLight->setPosition(Vector4(0.f, 0.f, 1.f, 0.f));

    m_spotLight->setPosition(Vector4(0.f, 11.f, 0.f, 1.f));
    m_spotLight->setSpotDirection(Vector3(0.f, 0.f, 0.f));
    m_spotLight->setSpotAngle(25.f);
    m_spotLight->setSpotExponent(20.f);
    m_spotLight->setLinearAttenuation(.01f);
    m_spotLight->setQuadraticAttentuation(0.f);
    m_spotLight->setConstantAttenuation(1.f);
    m_spotLight->setDirectional(true);

    m_pointLight->setPosition(Vector4(11.f, 0.f, 0.f, 1.f));
    m_pointLight->setSpotAngle(180.f);
    m_pointLight->setQuadraticAttentuation(.025f);

    thread bear(&OBJObject::generateMesh, m_bear, "objects/bear.obj");
    thread bunny(&OBJObject::generateMesh, m_bunny, "objects/bunny.obj");
    thread dragon(&OBJObject::generateMesh, m_dragon, "objects/dragon.obj");

    std::this_thread::yield();

    bear.join();
    bunny.join();
    dragon.join();

    m_bear->loadVabo();
    m_bunny->loadVabo();
    m_dragon->loadVabo();

    m_sphere->m_material = materialFactory.make("polished gold");
    m_bear->m_material = materialFactory.make("red rubber");
    m_bunny->m_material = materialFactory.make("some color");
    m_dragon->m_material = materialFactory.make("jade");

    rescale();
}

void Window::rescale() {
    Matrix4 scale;
    scale.makeScale(.738f);
    m_bunny->m_toWorld = m_bunny->m_toWorld * scale;
    scale.makeScale(.912f);
    m_dragon->m_toWorld = m_dragon->m_toWorld * scale;
    scale.makeScale(.904f);
    m_bear->m_toWorld = m_bear->m_toWorld * scale;
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
    glLoadMatrixf(Globals::camera.getInverseMatrix().ptr());

    //Bind the light to slot 0.  We do this after the camera matrix is loaded so that
    //the light m_position will be treated as world coordiantes
    //(if we didn't the light would move with the camera, why is that?)
   // Globals::light.bind(0);
    Globals::light.unbind();
    m_directionalLight->bind(1);
    m_pointLight->bind(2);
    m_spotLight->bind(3);

    m_pointLight->debugDraw();
    m_spotLight->debugDraw();

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
        case '0':
            m_light = nullptr;
            break;
        case '1':
            m_light = m_directionalLight;
            break;
        case '2':
            m_light = m_pointLight;
            break;
        case '3':
            m_light = m_spotLight;
            break;
        case 'r':
            m_light = nullptr;
            m_model->m_toWorld.identity();
            rescale();
            break;
        case 's':
            m_light = nullptr;
            matrix.makeScale(.9f);
            m_model->m_toWorld = m_model->m_toWorld * matrix;
            break;
        case 'S':
            m_light = nullptr;
            matrix.makeScale(1.1f);
            m_model->m_toWorld = m_model->m_toWorld * matrix;
            break;
        default:
            break;
    }
    if(glutGetModifiers() & GLUT_ACTIVE_SHIFT) {
        m_shift = true;
    } else {
        m_shift = false;
    }
}


void Window::specialKeyCallback(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_F1:
            Globals::camera.reset();
            m_model = m_sphere;
            m_light = nullptr;
            break;
        case GLUT_KEY_F2:
            Globals::camera.reset();
            m_model = m_bunny;
            m_light = nullptr;
            break;
        case GLUT_KEY_F3:
            Globals::camera.reset();
            m_model = m_dragon;
            m_light = nullptr;
            break;
        case GLUT_KEY_F4:
            Globals::camera.reset();
            m_model = m_bear;
            m_light = nullptr;
            break;
        default:
            break;
    }
}

void Window::mouseButtonCallback(int button, int state, int x, int y) {
    switch(button) {
        case GLUT_LEFT_BUTTON:
            m_leftButton = state == GLUT_DOWN;
            if(m_leftButton) {
                prev = convertCoordinates(x, y);
            }
            break;
        case GLUT_RIGHT_BUTTON:
            m_rightButton = state == GLUT_DOWN;
            if(m_rightButton) {
                prev = Vector3(x, y, 0.f);
            }
            break;
    }
}


Vector3 Window::convertCoordinates(int x, int y) {
    Vector3 v;
    v.x = (2.f * x - width) / width;
    v.y = (height - 2.f * y) / height;
    v.z = 0.f;
    float distance = v.magnitude();
    if(distance > 1.f) {
        distance = 1.f;
    }
    v.z = sqrtf(1.f - (distance * distance));
    v.normalize();
    return v;
}

void Window::mouseMotionCallback(int x, int y) {
    if(m_shift) {
        Vector3 current = convertCoordinates(x, y);
        Matrix4 scale;
        if(current.y > prev.y) {
            scale.makeScale(1.03f);
        } else {
            scale.makeScale(.97f);
        }
        if(m_light) {
            if(m_light != m_directionalLight) {
                Vector3 loc = m_light->getPosition().toVector3();
                loc *= scale[0][0];
                m_light->setPosition(loc.toVector4(1.f));
            }
        } else {
            m_model->m_toWorld = m_model->m_toWorld * scale;
        }
        prev = current;
    } else if(m_leftButton) {
        Vector3 current = convertCoordinates(x, y);
        Vector3 axis = prev.cross(current);
        float v = (current - prev).magnitude();
        if(v > 0.001f) {
            Matrix4 rot;
            float angle = acosf(current.dot(prev) / (current.magnitude() * prev.magnitude()));
            rot.makeRotateArbitrary(axis, angle);
            if(m_light) {
                Vector4 lpos = m_light->getPosition();
                lpos = rot * lpos;
                m_light->setPosition(lpos);
                m_light->setSpotDirection(Vector3(0.f, 0.f, 0.f));
            } else {
                m_model->m_toWorld = rot * m_model->m_toWorld;
            }
        }
        prev = current;
    } else if(m_rightButton) {
        if(m_light && m_light == m_spotLight) {
            float dx = (x - prev.x);
            float dy = (y - prev.y);
            if(abs(dx) > abs(dy)) {
                if(m_light->getSpotExponent() >= 1.f && dx < 0) {
                    m_light->setSpotExponent(m_light->getSpotExponent() - 1);
                } else if(m_light->getSpotExponent() <= 179.f && dx > 0) {
                    m_light->setSpotExponent(m_light->getSpotExponent() + 1);
                }
            } else {
                if(m_light->getSpotAngle() >= 1.f && dy < 0) {
                    m_light->setSpotAngle(m_light->getSpotAngle() - 1);
                } else if (m_light->getSpotAngle() <= 179.f && dy > 0) {
                    m_light->setSpotAngle(m_light->getSpotAngle() + 1);
                }
            }
        } else {
            Matrix4 translate;
            translate.makeTranslate((x - prev.x) * .1f, (y - prev.y) * -.1f, 0.f);
            m_model->m_toWorld = translate * m_model->m_toWorld;
        }
        prev.x = x;
        prev.y = y;
    }

}
