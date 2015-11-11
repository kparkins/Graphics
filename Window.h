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
#include "skybox.h"
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

        void initialize();

        void idlecb();
        void reshapecb(int, int);
        void displaycb();
        void keycb(unsigned char key, int x, int y);
        void specialkeycb(int key, int x, int y);
        void mousebuttoncb(int, int, int, int);

        int width();
        int height();

        void width(int w);
        void height(int h);


    protected:

        skybox m_skybox;
        geode_ptr m_sphere;
        geode_ptr m_cube;
        camera_ptr m_camera;
        group_ptr m_scene;
        light_ptr m_directlight;
        light_ptr m_pointlight;

        mat4 m_worldscale;
        mat4 m_skyboxtrans;

        int frame;
        int timebase;
        int time;
        int m_width, m_height;                // window m_size

    };

    typedef shared_ptr<window> window_ptr;
}
#endif

