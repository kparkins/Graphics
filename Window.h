#ifndef WINDOW_H
#define WINDOW_H

#include <thread>
#include <memory>
#include <mutex>
#include <functional>
#include <unistd.h>

#include "OBJObject.h"
#include "MaterialFactory.h"
#include "Light.h"
#include "Camera.h"
#include "Sphere.h"
#include "Robot.h"
#include "Cube.h"
#include "Platoon.h"
#include "MatrixTransform.h"
#include "Globals.h"

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
    static void doShit(Matrix4 & c);
    static void runSquadAnim();

    static GeodePtr m_sphere;
    static GeodePtr m_cube;
    static CameraPtr m_camera;
    static GroupPtr m_scene;
    static GeodePtr m_robot;
    static Frustrum frustrum;


    static PlatoonPtr squad1;
    static PlatoonPtr squad2;
    static MatrixTransformPtr squad1Rot;
    static MatrixTransformPtr squad1Trans;
    static MatrixTransformPtr squad2Rot;
    static MatrixTransformPtr squad2Trans;
    static MatrixTransformPtr squad2scale;
    static MatrixTransformPtr squad1scale;
    static Matrix4 worldScale;

    static bool runAnimation;
    static int frame;
    static int timebase;
    static int time;

};

#endif

