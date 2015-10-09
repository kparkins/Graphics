#ifndef WINDOW_H
#define WINDOW_H

#include <memory>

#include "Drawable.h"

using std::make_pair;
using std::shared_ptr;
using std::make_shared;

class Window {
    
public:
    
    static int width, height; 	            // window m_size

    static void initialize(void);
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
    static void keyCallback(unsigned char key, int x, int y);
    static void specialKeyCallback(int key, int x, int y);

    static DrawablePtr m_model;
    static DrawablePtr m_cube;
    static DrawablePtr m_house;
    static DrawablePtr m_sphere;

};

#endif

