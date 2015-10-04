#ifndef GLOBALS_H
#define GLOBALS_H

#include "Camera.h"
#include "Cube.h"
#include "Light.h"
#include "DrawData.h"
#include "Sphere.h"
#include "UpdateData.h"



class Globals {
    
public:
    
    static Camera camera;
    static Cube cube;
    static Light light;
    static DrawData drawData;
    static UpdateData updateData;
    static Sphere sphere;

    static float spinValue;
    static bool useSphere;

    //Feel free to add more member variables as needed
    
};

#endif
