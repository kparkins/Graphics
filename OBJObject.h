#ifndef OBJOBJECT_H
#define OBJOBJECT_H

#include <iostream>
#include <vector>
#include <string>
#include <OpenGL/OpenGL.h>
#include <memory>

#include "Vector3.h"
#include "Drawable.h"

using std::shared_ptr;

class OBJObject : public Drawable {
    
public:
    
    OBJObject();
    virtual ~OBJObject(void);

    void load(std::string);
    virtual void draw(DrawData&);
    virtual void update(UpdateData&);
    
protected:
    
    //Helper functions
    std::vector<std::string>& split(const std::string&, char, std::vector<std::string>&);
    std::vector<std::string> split(const std::string&, char);
    
    //Parse
    void generateMesh();
    
    //Storage vectors
    std::vector<float> m_vertices;
    std::vector<float> m_normals;
    std::vector<float> m_colors;
    std::vector<int> m_faces;

    GLuint m_vbo;
    GLuint m_vao;

    size_t m_numVertices;

};

typedef shared_ptr<OBJObject> OBJObjectPtr;

#endif
