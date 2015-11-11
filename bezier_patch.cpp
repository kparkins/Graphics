#include "bezier_patch.h"

gfx::bezier_patch::bezier_patch(size_t fidelity)
        : m_fidelity(fidelity),
          m_vertices(fidelity, fidelity),
          m_normals(fidelity, fidelity),
          m_controlpoints(4, 4) {
}

gfx::bezier_patch::~bezier_patch() {

}

void gfx::bezier_patch::fidelity(size_t f) {
    this->m_fidelity = f;
}

size_t gfx::bezier_patch::fidelity() {
    return this->m_fidelity;
}

void gfx::bezier_patch::draw(mat4 & c) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(c.ptr());
    glBegin(GL_QUADS);

    glColor3f(1.f, 1.f, 1.f);
    for(size_t i = 0; i < m_fidelity - 1; ++i) {
        for(size_t j = 0; j < m_fidelity - 1; ++j) {
            glNormal3fv(vec3(0.f, 0.f, 1.f).ptr());
            glVertex3fv(m_vertices[i][j].ptr());

            glNormal3fv(vec3(0.f, 0.f, 1.f).ptr());
            glVertex3fv(m_vertices[i][j + 1].ptr());

            glNormal3fv(vec3(0.f, 0.f, 1.f).ptr());
            glVertex3fv(m_vertices[i + 1][j + 1].ptr());

            glNormal3fv(vec3(0.f, 0.f, 1.f).ptr());
            glVertex3fv(m_vertices[i + 1][j].ptr());
            //std::cout << m_vertices[i][j].x << " " << m_vertices[i][j].y << " " << m_vertices[i][j].z << " " << std::endl;
        }
    }

    glEnd();
    glPopMatrix();
}

float gfx::bezier_patch::bernstein(unsigned int i, float t, unsigned int n) {
    return static_cast<float>(
            math::factorial(n) / static_cast<float>(math::factorial(n - i) * math::factorial(i)) *
            pow(t, i) * pow(1.f - t, n - i)
    );
}

gfx::vec4 gfx::bezier_patch::eval_curve(float t, const vec4 & p0, const vec4 & p1, const vec4 & p2, const vec4 & p3) {
    vec4 p;
    float b0 = bernstein(0, t);
    float b1 = bernstein(1, t);
    float b2 = bernstein(2, t);
    float b3 = bernstein(3, t);
    //std::cout << b0 << " " << b1 << " " << b2 << " " << b3 << std::endl;
    p.x = p0.x * b0 + p1.x * b1 + p2.x * b2 + p3.x * b3;
    p.y = p0.y * b0 + p1.y * b1 + p2.y * b2 + p3.y * b3;
    p.z = p0.z * b0 + p1.z * b1 + p2.z * b2 + p3.z * b3;
    p.w = 1.f;

    std::cout << p.x << " " << p.y << " " << p.z << " " << p.w << std::endl;
    return p;
}

void gfx::bezier_patch::generate_vertices() {
    vec4 q0, q1, q2, q3;
    float u = 0.f;
    float delta = 1.f / static_cast<float>(m_fidelity);

    for(size_t i = 0; i < m_fidelity; ++i) {
        float v = 0.f;
        q0 = eval_curve(u, m_controlpoints[0][0], m_controlpoints[0][1], m_controlpoints[0][2], m_controlpoints[0][3]);
        q1 = eval_curve(u, m_controlpoints[1][0], m_controlpoints[1][1], m_controlpoints[1][2], m_controlpoints[1][3]);
        q2 = eval_curve(u, m_controlpoints[2][0], m_controlpoints[2][1], m_controlpoints[2][2], m_controlpoints[2][3]);
        q3 = eval_curve(u, m_controlpoints[3][0], m_controlpoints[3][1], m_controlpoints[3][2], m_controlpoints[3][3]);
        for(size_t j = 0; j < m_fidelity; ++j) {
            m_vertices[i][j] = eval_curve(v, q0, q1, q2, q3);
            v += delta;
        }
        u += delta;
    }
}

