#ifndef VECTOR4_H
#define VECTOR4_H

#include <string>

class Vector3;

class Vector4 {
    
public:
    
    Vector4();
    Vector4(float, float, float);
    Vector4(float, float, float, float);
    
    float* ptr();
    float& operator[](int);
    
    void set(float,float,float,float);
    
    
    Vector4 add(Vector4&);
    Vector4 operator+(Vector4);
    
    Vector4 subtract(Vector4&);
    Vector4 operator-(Vector4);
    
    Vector4 dehomogenize();
    
    Vector3 toVector3();
    
    float dot(Vector4);
    
    void print(std::string);

protected:
    
    __attribute__ ((aligned(16))) float m[4];

};

#endif
