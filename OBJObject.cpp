#include "OBJObject.h"


OBJObject::OBJObject() {
}

OBJObject::~OBJObject() {
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}

void OBJObject::render() {
    //m_material.apply();
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    //glMultMatrixf(m_toWorld.ptr());
    glBindVertexArray(m_vao);

    glDrawArrays(GL_TRIANGLES, 0, m_numVertices);

    glBindVertexArray(0);
    glPopMatrix();
}

void OBJObject::generateMesh(std::string filename) {
    int vi, vni;
    size_t pos;
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
            if(tokens.size() >= 7) {
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
        } else if(tokens[0] == "f") {
            for (size_t i = 0; i < 3; ++i) {
                unsigned long pos2;
                std::string & tok = tokens[i + 1];

                pos = tok.find("/");
                pos2 = tok.find_last_of("/");

                vi = std::stoi(tok.substr(0, pos));
                vni = std::stoi(tok.substr(pos2 + 1));

                m_faces.push_back(vi - 1);
                m_faces.push_back(vni - 1);
                m_faces.push_back(vi - 1);
            }
        }
    }
    this->generateInterleavedArray();
    std::cout << filename + "\tDone." << std::endl;
}

void OBJObject::generateInterleavedArray() {
    int colorIndex, normalIndex, vertexIndex;
    for(int i = 0; i < m_faces.size(); i += 3) {
        colorIndex = 3 *  m_faces[i];
        normalIndex = 3 * m_faces[i + 1];
        vertexIndex = 3 * m_faces[i + 2];
        m_interleaved.push_back(m_colors[colorIndex]);
        m_interleaved.push_back(m_colors[colorIndex + 1]);
        m_interleaved.push_back(m_colors[colorIndex + 2]);
        m_interleaved.push_back(m_normals[normalIndex]);
        m_interleaved.push_back(m_normals[normalIndex + 1]);
        m_interleaved.push_back(m_normals[normalIndex + 2]);
        m_interleaved.push_back(m_vertices[vertexIndex]);
        m_interleaved.push_back(m_vertices[vertexIndex + 1]);
        m_interleaved.push_back(m_vertices[vertexIndex + 2]);
    }
    m_numVertices = m_interleaved.size() / 9;
}


void OBJObject::loadVabo() {
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_interleaved.size() * sizeof(float), &m_interleaved[0], GL_STATIC_DRAW);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, sizeof(float)* 9, (void*) 0);

    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, sizeof(float) * 9, (void*) (sizeof(float) * 3));

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(float) * 9, (void*) (sizeof(float) * 6));

    glBindVertexArray(0);
}

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
