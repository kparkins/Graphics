#ifndef OBJOBJECT_H
#define OBJOBJECT_H

#include <iostream>
#include <vector>
#include <string>
#include <OpenGL/OpenGL.h>
#include "Vector3.h"
#include "Drawable.h"

struct Face {
    int vertexIndices[3];
    int normalIndices[3];
    int colorIndices[3];
};


class OBJObject : public Drawable {
    
public:
    
    OBJObject(std::string);
    virtual ~OBJObject(void);
    
    virtual void draw(DrawData&);
    virtual void update(UpdateData&);
    
protected:
    
    //Helper functions
    std::vector<std::string>& split(const std::string&, char, std::vector<std::string>&);
    std::vector<std::string> split(const std::string&, char);
    
    //Parse
    void parse(std::string&);
    void generateVBO();
    
    //Storage vectors
    std::vector<Vector3*>* m_vertices;
    std::vector<Vector3*>* m_normals;
    std::vector<Face*>* m_faces;
    std::vector<Color*>* m_colors;
    size_t m_vboSize;

    GLuint m_vbo;

    /*std::vector<float> m_vertices;
    std::vector<float> m_colors;
    std::vector<float> m_normals;
    std::vector<int> m_faces; */


};

#endif
