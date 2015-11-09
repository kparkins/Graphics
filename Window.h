#ifndef GFX_WINDOW_H
#define GFX_WINDOW_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <mutex>
#include <thread>
#include <memory>
#include <unistd.h>
#include <iostream>
#include <functional>

#include "cube.h"
#include "light.h"
#include "camera.h"
#include "sphere.h"
#include "triangle_mesh.h"
#include "material_factory.h"
#include "matrix_transform.h"

using std::make_pair;
using std::shared_ptr;
using std::make_shared;
using std::placeholders::_1;
using std::thread;

namespace gfx {
    class window {

    public:

        static int width, height;                // window m_size
        static void initialize(void);

        static void idlecb(void);
        static void reshapecb(int, int);
        static void displaycb(void);
        static void keycb(unsigned char key, int x, int y);
        static void specialkeycb(int key, int x, int y);
        static void mousebuttoncb(int, int, int, int);

        static geode_ptr m_sphere;
        static geode_ptr m_cube;
        static camera_ptr m_camera;
        static group_ptr m_scene;

        static mat4 world_scale;

        static int frame;
        static int timebase;
        static int time;

    };
}
#endif

