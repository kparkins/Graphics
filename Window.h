#ifndef WINDOW_H
#define WINDOW_H

#include <thread>
#include <memory>
#include <mutex>
#include <functional>
#include <unistd.h>

#include "OBJObject.h"
#include "Drawable.h"
#include "MaterialFactory.h"
#include "Light.h"

using std::make_pair;
using std::shared_ptr;
using std::make_shared;
using std::placeholders::_1;
using std::thread;

class Window {
    
public:
    
    static int width, height; 	            // window m_size
    static bool m_leftButton;
    static bool m_rightButton;
    static void initialize(void);
    static LightPtr m_directionalLight;
    static LightPtr m_pointLight;
    static LightPtr m_spotLight;
    static LightPtr m_light;
    static Vector3 prev;

    static void idleCallback(void);
    static Vector3 convertCoordinates(int x, int y);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
    static void keyCallback(unsigned char key, int x, int y);
    static void specialKeyCallback(int key, int x, int y);
    static void mouseButtonCallback(int, int, int, int);
    static void mouseMotionCallback(int x, int y);

    static DrawablePtr m_model;
    static DrawablePtr m_sphere;

    static OBJObjectPtr m_bunny;
    static OBJObjectPtr m_bear;
    static OBJObjectPtr m_dragon;

    static int frame;
    static int timebase;
    static int time;

};

#endif

