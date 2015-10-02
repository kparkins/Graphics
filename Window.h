#ifndef WINDOW_H
#define WINDOW_H

class Window {
    
public:
    
    static int width, height; 	            // window size
    static float spinValue;
    
    static void initialize(void);
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
    static void keyCallback(unsigned char key, int x, int y);
    
};

#endif

