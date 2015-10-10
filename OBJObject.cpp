#include "OBJObject.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#define glGenVertexArrays glGenVertexArraysAPPLE
#define glBindVertexArray glBindVertexArrayAPPLE
#define glDeleteVertexArrays glDeleteVertexArraysAPPLE
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "math.h"
#include <sstream>
#include <fstream>

#define deleteVector(__type__, __vect__) do {\
                                   std::vector<__type__>::iterator iter; \
                                   std::vector<__type__>::iterator end; \
                                   iter = __vect__->begin();\
                                   end = __vect__->end();\
                                   while(iter != end) delete (*(iter++));\
                                   delete __vect__;\
                               } while(false)


OBJObject::OBJObject() : Drawable() {
}

OBJObject::~OBJObject() {
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}

void OBJObject::draw(DrawData& data) {
    m_material.apply();
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(m_toWorld.ptr());

    glBindVertexArray(m_vao);

    glDrawArrays(GL_TRIANGLES, 0, m_numVertices);

    glBindVertexArray(0);

    glPopMatrix();
}

void OBJObject::update(UpdateData& data) {
    //
}

void OBJObject::load(std::string filename) {
    int vi;
    int vni;
    size_t pos;
    size_t vsize;
    std::string line;
    Vector3 normalizer;
    std::ifstream infile(filename);
    std::vector<std::string> tokens;

    while (std::getline(infile, line)) {
        tokens.resize(0);
        tokens = split(line, ' ', tokens);
        if(tokens[0] == "v") {
            m_vertices.push_back(std::stof(tokens[1]));
            m_vertices.push_back(std::stof(tokens[2]));
            m_vertices.push_back(std::stof(tokens[3]));
            if(tokens.size() >= 6) {
                m_colors.push_back(std::stof(tokens[4]));
                m_colors.push_back(std::stof(tokens[5]));
                m_colors.push_back(std::stof(tokens[6]));
            } else {
                m_colors.push_back(0.f);
                m_colors.push_back(0.5f);
                m_colors.push_back(0.5f);
            }
        } else if(tokens[0] == "vn") {
            normalizer.x = std::stof(tokens[1]);
            normalizer.y = std::stof(tokens[2]);
            normalizer.z = std::stof(tokens[3]);
            normalizer.normalize();
            float* fptr = normalizer.ptr();
            for(int i = 0; i < 3; ++i) {
                m_normals.push_back(*fptr++);
            }
        } else if(tokens[0] == "f") {            // TODO // is not the delimeter / is in between can be texs
            for (size_t i = 0; i < 3; ++i) {
                std::string & tok = tokens[i + 1];
                pos = tok.find("//");
                vi = std::stoi(tok.substr(0, pos));
                vni = std::stoi(tok.substr(pos + 2));
                m_faces.push_back(vi - 1);
                m_faces.push_back(vni - 1);
                m_faces.push_back(vi - 1);
            }
        }
    }
    this->generateMesh();
}

void OBJObject::generateMesh() {
    int colorIndex, normalIndex, vertexIndex;
    std::vector<float> interleaved;
    for(int i = 0; i < m_faces.size(); i += 3) {
        colorIndex = 3 * m_faces[i];
        normalIndex = 3 * m_faces[i + 1];
        vertexIndex = 3 * m_faces[i + 2];
        interleaved.push_back(m_colors[colorIndex]);
        interleaved.push_back(m_colors[colorIndex + 1]);
        interleaved.push_back(m_colors[colorIndex + 2]);
        interleaved.push_back(m_normals[normalIndex]);
        interleaved.push_back(m_normals[normalIndex + 1]);
        interleaved.push_back(m_normals[normalIndex + 2]);
        interleaved.push_back(m_vertices[vertexIndex]);
        interleaved.push_back(m_vertices[vertexIndex + 1]);
        interleaved.push_back(m_vertices[vertexIndex + 2]);
    }
    m_numVertices = interleaved.size() / 9;

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, interleaved.size() * sizeof(float), &interleaved[0], GL_STATIC_DRAW);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, sizeof(float)* 9, (void*) 0);

    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, sizeof(float) * 9, (void*) (sizeof(float) * 3));

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(float) * 9, (void*) (sizeof(float) * 6));

    glBindVertexArray(0);
    std::cout << std::setw(10) << "Done." << std::endl;
}

//Split functions from the interwebs
//http://stackoverflow.com/questions/236129/split-a-string-in-c
std::vector<std::string>& OBJObject::split(const std::string &s, char delim,
                                           std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> OBJObject::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
