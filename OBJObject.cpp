#include "OBJObject.h"


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

void OBJObject::generateMesh(std::string filename) {
    int vi, vni, colorIndex, normalIndex, vertexIndex;
    size_t pos, vsize;
    std::string line;
    Vector3 normalizer;
    std::vector<int> faces;
    std::ifstream infile(filename);
    std::vector<std::string> tokens;
    std::vector<float> vertices, normals, colors;

    while (std::getline(infile, line)) {
        tokens.resize(0);
        tokens = split(line, ' ', tokens);
        if(tokens[0] == "v") {
            vertices.push_back(std::stof(tokens[1]));
            vertices.push_back(std::stof(tokens[2]));
            vertices.push_back(std::stof(tokens[3]));
            if(tokens.size() >= 6) {
                colors.push_back(std::stof(tokens[4]));
                colors.push_back(std::stof(tokens[5]));
                colors.push_back(std::stof(tokens[6]));
            } else {
                colors.push_back(0.f);
                colors.push_back(0.5f);
                colors.push_back(0.5f);
            }
        } else if(tokens[0] == "vn") {
            normalizer.x = std::stof(tokens[1]);
            normalizer.y = std::stof(tokens[2]);
            normalizer.z = std::stof(tokens[3]);
            normalizer.normalize();
            float* fptr = normalizer.ptr();
            for(int i = 0; i < 3; ++i) {
                normals.push_back(*fptr++);
            }
        } else if(tokens[0] == "f") {            // TODO // is not the delimeter / is in between can be texs
            for (size_t i = 0; i < 3; ++i) {
                std::string & tok = tokens[i + 1];
                pos = tok.find("//");
                vi = std::stoi(tok.substr(0, pos));
                vni = std::stoi(tok.substr(pos + 2));
                faces.push_back(vi - 1);
                faces.push_back(vni - 1);
                faces.push_back(vi - 1);
            }
        }
    }
    for(int i = 0; i < faces.size(); i += 3) {
        colorIndex = 3 * faces[i];
        normalIndex = 3 * faces[i + 1];
        vertexIndex = 3 * faces[i + 2];
        m_interleaved.push_back(colors[colorIndex]);
        m_interleaved.push_back(colors[colorIndex + 1]);
        m_interleaved.push_back(colors[colorIndex + 2]);
        m_interleaved.push_back(normals[normalIndex]);
        m_interleaved.push_back(normals[normalIndex + 1]);
        m_interleaved.push_back(normals[normalIndex + 2]);
        m_interleaved.push_back(vertices[vertexIndex]);
        m_interleaved.push_back(vertices[vertexIndex + 1]);
        m_interleaved.push_back(vertices[vertexIndex + 2]);
    }
    m_numVertices = m_interleaved.size() / 9;
    std::cout << filename + "\tDone." << std::endl;
}

void OBJObject::loadVao() {
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
