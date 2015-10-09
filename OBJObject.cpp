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
    this->m_vertices = new std::vector<Vector3*>();
    this->m_normals = new std::vector<Vector3*>();
    this->m_faces = new std::vector<Face*>();
    this->m_colors = new std::vector<Color*>();
    
    parse(filename);
}

OBJObject::~OBJObject() {
    //Delete any dynamically allocated memory/objects here
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
}

void OBJObject::draw(DrawData& data) {
    m_material.apply();
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(m_toWorld.ptr());

    glEnable(GL_LIGHTING);
    glBegin(GL_TRIANGLES);
    
    //Loop through the m_faces
    //For each face:
    //  Look up the m_vertices, normals (if they exist), and texcoords (if they exist)
    //  Draw them as triplets:
    
    //      glNorm(normals->at(face.normalIndices[0]))
    //      glVert(m_vertices->at(face.vertexIndices[0]))
    //      Etc.
    //

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
    
    glEnd();
    
    glPopMatrix();
}

void OBJObject::update(UpdateData& data) {
    //
}

void OBJObject::parse(std::string& filename) {
    std::ifstream infile(filename);
    std::string line;
    std::vector<std::string> tokens;
    std::string token;
    
    int lineNum = 0;
    

    //While all your lines are belong to us
    while (std::getline(infile, line)) {
        tokens.clear();
        tokens = split(line, ' ', tokens);

        //Parse the vertex line
        if(tokens.at(0).compare("v") == 0) {
            float x = std::stof(tokens.at(1));
            float y = std::stof(tokens.at(2));
            float z = std::stof(tokens.at(3));

#ifdef __GNUC__
            m_vertices->push_back(new Vector3(x, y, z));
#elif _WIN32
            void* ptr = _aligned_malloc(sizeof(Vector3), 16);
			Vector3* vec = new(ptr) Vector3(x, y, z);
			m_vertices->push_back(vec);
#endif
            if(tokens.size() >= 6) {
                float r = std::stof(tokens.at(4));
                float g = std::stof(tokens.at(5));
                float b = std::stof(tokens.at(6));
                m_colors->push_back(new Color(r, g, b));
            }

        } else if(tokens.at(0).compare("vn") == 0) {
            Vector3* normal = new Vector3();
            normal->x = std::stof(tokens.at(1));
            normal->y = std::stof(tokens.at(2));
            normal->z = std::stof(tokens.at(3));
            normal->normalize();
            m_normals->push_back(normal);
        } else if(tokens.at(0).compare("f") == 0) {
            Face *face = new Face();
            for (size_t i = 0; i < 3; ++i) {
                std::string &tok = tokens[i + 1];
                size_t pos = tok.find("//");
                int vi = std::stoi(tok.substr(0, pos));
                int vni = std::stoi(tok.substr(pos + 2));
                face->vertexIndices[i] = vi - 1;
                face->normalIndices[i] = vni - 1;
                face->colorIndices[i] = vi - 1;
            }
            m_faces->push_back(face);
        }
    }
    
    std::cout << "Done parsing." << std::endl;
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
