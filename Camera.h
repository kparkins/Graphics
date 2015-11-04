#ifndef CAMERA_H
#define CAMERA_H

#include <memory>

#include "Matrix4.h"
#include "Vector3.h"

using std::shared_ptr;

class Camera {
    
public:
    
    Vector3 e;   //Center of Projection
    Vector3 d;   //Look At
    Vector3 up;  //Up Vector ^
    float fov;
    
    Camera(void);
    ~Camera(void);
    
    void update(void);
    void reset();
    
    Matrix4& getMatrix(void);
    Matrix4& getInverseMatrix(void);
    
    void set(Vector3&, Vector3&, Vector3&);
    
protected:
    
    Matrix4 c;   //Camera Matrix
    Matrix4 ci;  //Inverse of Camera Matrix
    
};

typedef shared_ptr<Camera> CameraPtr;

#endif
