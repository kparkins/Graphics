#ifndef WINDOW_H
#define WINDOW_H

#include "InputHandler.h"

class Window {
    
public:
    
    static int width, height; 	            // window size

    static void initialize(void);
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
    static void keyCallback(unsigned char key, int x, int y);

    static InputHandler m_inputHandler;

};

#endif

