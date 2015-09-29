#ifndef WINDOW_H
#define WINDOW_H

class Window {
    
public:
    
    static int width, height; 	            // window size
    
    static void initialize(void);
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
    
};

#endif

