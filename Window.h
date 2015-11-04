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
    static void initialize(void);
    static LightPtr m_directionalLight;

    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
    static void keyCallback(unsigned char key, int x, int y);
    static void specialKeyCallback(int key, int x, int y);
    static void mouseButtonCallback(int, int, int, int);

    static DrawablePtr m_sphere;

    static int frame;
    static int timebase;
    static int time;

};

#endif

