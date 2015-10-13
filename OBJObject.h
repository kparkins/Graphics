#ifndef OBJOBJECT_H
#define OBJOBJECT_H

#ifdef __APPLE__
#include <GLUT/glut.h>
    #define glGenVertexArrays glGenVertexArraysAPPLE
    #define glBindVertexArray glBindVertexArrayAPPLE
    #define glDeleteVertexArrays glDeleteVertexArraysAPPLE
#else
#include <GL/glut.h>
#endif

#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>
#include <OpenGL/OpenGL.h>

#include "Vector3.h"
#include "Drawable.h"

using std::string;
using std::vector;
using std::shared_ptr;

class OBJObject : public Drawable {
    
public:
    
    OBJObject();
    virtual ~OBJObject(void);

    void generateMesh(string);
    void loadVabo();

    const vector<float>& getVertices();

    virtual void draw(DrawData&);
    virtual void update(UpdateData&);
    
protected:
    
    //Helper functions
    vector<string>& split(const string&, char, vector<string>&);
    vector<string> split(const string&, char);

    //Storage vectors
    vector<float> m_interleaved;

    GLuint m_vbo;
    GLuint m_vao;

    size_t m_numVertices;

};

typedef shared_ptr<OBJObject> OBJObjectPtr;

#endif
