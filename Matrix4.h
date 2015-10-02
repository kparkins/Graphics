#ifndef MATRIX4_H
#define MATRIX4_H

#include <cassert>
#include <string>

class Vector3;
class Vector4;

class Matrix4 {

public:
    
    Matrix4();
    Matrix4(float, float, float, float,
            float, float, float, float,
            float, float, float, float,
            float, float, float, float);
    
    void set(float, float, float, float,
             float, float, float, float,
             float, float, float, float,
             float, float, float, float);
    
    float get(int,int);
    
    Matrix4& operator=(Matrix4);
    float* operator[](int);
    
    float* ptr();
    
    void identity();
    
    Matrix4 multiply(Matrix4);
    Matrix4 operator*(Matrix4);
    Vector4 multiply(Vector4);
    Vector4 operator*(Vector4);
    Vector3 multiply(Vector3);
    Vector3 operator*(Vector3);
    
    Matrix4 makeRotateX(float);
    Matrix4 makeRotateY(float);
    Matrix4 makeRotateZ(float);
    Matrix4 makeRotateArbitrary(Vector3, float);
    
    Matrix4 makeScale(float, float, float);
    Matrix4 makeScale(float);
    
    Matrix4 makeTranslate(float, float, float);
    Matrix4 makeTranslate(Vector3);
    
    Matrix4 transpose(void);
    Matrix4 inverse(void);
    Matrix4 rigidInverse(void);
    
    Matrix4 makePerspectiveProjection(float, float, float, float, float);
    Matrix4 makeViewport(float, float, float, float);
    
    void print(std::string);
    
protected:
    
    float m[4][4];
    
};

#endif
