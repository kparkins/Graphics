#include "triangle_mesh.h"


gfx::triangle_mesh::triangle_mesh() {

}

gfx::triangle_mesh::~triangle_mesh() {
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}

void gfx::triangle_mesh::render() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, m_numverts);
    glBindVertexArray(0);

    glPopMatrix();
}

void gfx::triangle_mesh::generate_mesh(std::string filename) {
    int vi, vni;
    size_t pos;
    std::string line;
    vec3 normalizer;
    std::ifstream infile(filename);
    std::vector<std::string> tokens;

    while (std::getline(infile, line)) {
        tokens.resize(0);
        tokens = split(line, ' ', tokens);
        if(tokens[0] == "v") {
            m_properties |= VERTICES;
            m_vertices.push_back(std::stof(tokens[1]));
            m_vertices.push_back(std::stof(tokens[2]));
            m_vertices.push_back(std::stof(tokens[3]));
            if(tokens.size() >= 7) {
                m_properties |= COLORS;
                m_colors.push_back(std::stof(tokens[4]));
                m_colors.push_back(std::stof(tokens[5]));
                m_colors.push_back(std::stof(tokens[6]));
            } else {
                m_colors.push_back(0.f);
                m_colors.push_back(0.5f);
                m_colors.push_back(0.5f);
            }
        } else if(tokens[0] == "vn") {
            m_properties |= NORMALS;
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
    this->flatten();
    std::cout << filename + "\tDone." << std::endl;
}

void gfx::triangle_mesh::flatten() {
    int ci, ni, vi;
    for(int i = 0; i < m_faces.size(); i += 3) {
        ci = 3 *  m_faces[i];
        ni = 3 * m_faces[i + 1];
        vi= 3 * m_faces[i + 2];
        m_interleaved.push_back(m_colors[ci]);
        m_interleaved.push_back(m_colors[ci + 1]);
        m_interleaved.push_back(m_colors[ci + 2]);
        m_interleaved.push_back(m_normals[ni]);
        m_interleaved.push_back(m_normals[ni + 1]);
        m_interleaved.push_back(m_normals[ni + 2]);
        m_interleaved.push_back(m_vertices[vi]);
        m_interleaved.push_back(m_vertices[vi + 1]);
        m_interleaved.push_back(m_vertices[vi + 2]);
    }
    m_numverts = m_interleaved.size() / 9;
}

void gfx::triangle_mesh::buffer_mesh(){
    int offset = 0;
    int stride = calculate_stride(m_properties);
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_interleaved.size() * sizeof(float), &m_interleaved[0], GL_STATIC_DRAW);

    if(m_properties & COLORS) {
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(3, GL_FLOAT, sizeof(float) * stride, (void *) 0);
        offset += 3;
    }

    if(m_properties & NORMALS) {
        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(GL_FLOAT, sizeof(float) * stride, (void*) (sizeof(float) * offset));
        offset += 3;
    }

    if(m_properties & TEXTURES) {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(3, GL_FLOAT, sizeof(float) * stride, (void*) (sizeof(float) * offset));
        offset += 3;
    }

    if(m_properties & VERTICES) {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, sizeof(float) * stride, (void *) (sizeof(float) * offset));
    }

    glBindVertexArray(0);
}

unsigned int gfx::triangle_mesh::calculate_stride(unsigned int props) {
    unsigned int stride = 0;
    stride += (props & VERTICES) ? 3 : 0;
    stride += (props & COLORS) ? 3 : 0;
    stride += (props & NORMALS) ? 3 : 0;
    stride += (props & TEXTURES) ? 3 : 0;
    return stride;
}

std::vector<std::string>& gfx::triangle_mesh::split(const std::string &s, char delim,
                                           std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

