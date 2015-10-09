#include "OBJObject.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
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


OBJObject::OBJObject(std::string filename) : Drawable() {
   /* this->m_vertices = new std::vector<Vector3*>();
    this->m_normals = new std::vector<Vector3*>();
    this->m_faces = new std::vector<Face*>();
    this->m_colors = new std::vector<Color*>();
    */
    parse(filename);
}

OBJObject::~OBJObject() {
   /* //Delete any dynamically allocated memory/objects here
#ifdef __GNUC__
    deleteVector(Vector3*, m_vertices);
#elif _WIN32
	for (auto it = m_vertices->begin(); it != m_vertices->end(); ++it) {
		(*it)->~Vector3();
		free(static_cast<void*>(*it));
	}
#endif
    deleteVector(Vector3*, m_normals);
    deleteVector(Face*, m_faces);
    deleteVector(Color*, m_colors);
    */
    glDeleteBuffers(1, &m_vbo);
}

void OBJObject::draw(DrawData& data) {
    m_material.apply();
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(m_toWorld.ptr());
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glDrawArrays(GL_TRIANGLES, m_vbo, m_faces.size() / 2);
//    glBegin(GL_TRIANGLES);
   /*
    Color* c;
    Vector3* v;
    Vector3* vn;
    Face* face;
    int* vertices;
    int* normals;
    int* colors;


    for(auto it = m_faces->begin(); it != m_faces->end(); ++it) {
        face = *it;
        vertices = &face->vertexIndices[0];
        normals = &face->normalIndices[0];
        colors = &face->colorIndices[0];

        for(int i = 0; i < 3; ++i) {
            if(m_colors->size() > 0) {
                c = m_colors->at(colors[i]);
                glColor3fv(c->ptr());
            }
            v = m_vertices->at(vertices[i]);
            vn = m_normals->at(normals[i]);
            glNormal3fv(vn->ptr());
            glVertex3fv(v->ptr());
        }
    }
    */
  //  glEnd();
    
    glPopMatrix();
}

void OBJObject::update(UpdateData& data) {
    //
}

void OBJObject::parse(std::string& filename) {
    FILE* fp;     // file pointer
    Vector3 temp;
    float* nptr;
    float x,y,z;  // vertex coordinates
    float r = 0.f;
    int f[6];
    float g = 0.5f;
    float b = 0.5f;  // vertex color
    char c1,c2;    // characters read from file
    memset(static_cast<void*>(&f), 0, sizeof(int) * 6);

    fp = fopen(filename.c_str(),"rb");
    if (!fp) {
        std::cerr << "error loading file" << std::endl;
        exit(-1);
    }

    while (c1 != EOF && c2 != EOF) {
        c1 = fgetc(fp);
        c2 = fgetc(fp);
        if (c1 == 'v' && c2 == ' ') {
            fscanf(fp, "%f %f %f %f %f %f", &x, &y, &z, &r, &g, &b);
            m_vertices.push_back(x);
            m_vertices.push_back(y);
            m_vertices.push_back(z);
            m_colors.push_back(r);
            m_colors.push_back(g);
            m_colors.push_back(b);
        } else if (c1 == 'v' && c2 == 'n') {
            fscanf(fp, "%f %f %f", &temp.x, &temp.y, &temp.z);
            temp.normalize();
            nptr = temp.ptr();
            for(int i = 0; i < 3; ++i) {
               m_normals.push_back(*nptr++);
            }
        } else if (c1 == 'f' && c2 == ' ') {
            fscanf(fp, "%i//%i %i//%i %i//%i", &f[0], &f[1], &f[2], &f[3], &f[4], &f[5]);
            for(int i = 0; i < 6; ++i) {
                m_faces.push_back(f[i]);
            }
        }
    }
    fclose(fp);   // make sure you don't forget to close the file when done
    std::cout << "Done parsing...Generating vbo..." << std::endl;
    this->generateVBO();
}

void OBJObject::generateVBO() {
    size_t bufferSize = sizeof(float) * (m_normals.size() + m_colors.size() + m_vertices.size());
    std::vector<float> interleaved;
    for(int i = 0; i < m_faces.size(); i += 2) {
        int vindex = m_faces[i];
        int vnindex = m_faces[i + 1];
        interleaved.push_back(m_vertices[vindex]);
        interleaved.push_back(m_vertices[vindex + 1]);
        interleaved.push_back(m_vertices[vindex + 2]);
        interleaved.push_back(m_normals[vnindex]);
        interleaved.push_back(m_normals[vnindex + 1]);
        interleaved.push_back(m_normals[vnindex + 2]);
        interleaved.push_back(m_colors[vindex]);
        interleaved.push_back(m_colors[vindex + 1]);
        interleaved.push_back(m_colors[vindex + 2]);
    }
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, bufferSize, 0, GL_STATIC_DRAW);
    GLvoid* vbo = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    memcpy(vbo, static_cast<const void*>(interleaved.data()), sizeof(float) * interleaved.size());
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glVertexPointer(3, GL_FLOAT, sizeof(float) * 6, 0);
    glNormalPointer(GL_FLOAT, sizeof(float) * 6, (void*) (sizeof(float) * 3));
    glColorPointer(3, GL_FLOAT, sizeof(float)* 6, (void*) (sizeof(float) * 6));
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
