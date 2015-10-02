#ifndef CUBE_H
#define CUBE_H

#include "Drawable.h"
#include "Vector3.h"

class Cube : public Drawable {
    
public:
    
    float size;
    
    
    Cube(float);
    virtual ~Cube(void);
    
    virtual void draw(DrawData &);
    virtual void update(UpdateData &);
    
    void spin(float);
    void spinX(float);
    void spinY(float);
    void spinZ(float);
    void scale(float);
    void translate(Vector3 translate);
    
};

#endif

