#include "bezier_patch.h"
#include "material_factory.h"

gfx::bezier_patch::bezier_patch(size_t fidelity)
        : m_fidelity(fidelity),
          m_vertices(fidelity, fidelity),
          m_normals(fidelity, fidelity),
          m_controlpoints(4, 4),
          m_texcoords(fidelity, fidelity) {
}

gfx::bezier_patch::~bezier_patch() {

}

void gfx::bezier_patch::fidelity(size_t f) {
    this->m_fidelity = f;
}

size_t gfx::bezier_patch::fidelity() {
    return this->m_fidelity;
}

void gfx::bezier_patch::texture(texture_ptr t) {
    this->m_texture = t;
}

gfx::texture_ptr gfx::bezier_patch::texture() {
    return this->m_texture;
}

void gfx::bezier_patch::draw(mat4 & c) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(c.ptr());
    glEnable(GL_TEXTURE_2D);

    m_texture->bind();
    glDisable(GL_CULL_FACE);
    glBegin(GL_QUADS);

    for(size_t i = 0; i < m_fidelity - 1; ++i) {
        for(size_t j = 0; j < m_fidelity - 1; ++j) {

            glNormal3fv(m_normals[i][j].ptr());
            glTexCoord2f(m_texcoords[i][j].x, m_texcoords[i][j].y);
            glVertex3fv(m_vertices[i][j].ptr());

            glNormal3fv(m_normals[i][j + 1].ptr());
            glTexCoord2f(m_texcoords[i][j + 1].x, m_texcoords[i][j + 1].y);
            glVertex3fv(m_vertices[i][j + 1].ptr());

            glNormal3fv(m_normals[i + 1][j + 1].ptr());
            glTexCoord2f(m_texcoords[i + 1][j + 1].x, m_texcoords[i + 1][j + 1].y);
            glVertex3fv(m_vertices[i + 1][j + 1].ptr());

            glNormal3fv(m_normals[i + 1][j].ptr());
            glTexCoord2f(m_texcoords[i + 1][j].x, m_texcoords[i + 1][j].y);
            glVertex3fv(m_vertices[i + 1][j].ptr());
        }
    }

    glEnd();
    glEnable(GL_CULL_FACE);
    m_texture->unbind();
    glPopMatrix();
}

gfx::vec4 gfx::bezier_patch::eval_curve(float t, const vec4 & p0, const vec4 & p1, const vec4 & p2, const vec4 & p3) {
    vec4 p;
    float b0 = -(t * t * t) + 3 * (t * t) - 3 * t + 1.f;
    float b1 = 3 * t * t * t - 6 * t * t + 3 * t;
    float b2 = -3.f *  t * t * t + 3 * t * t;
    float b3 = t * t * t;

    p.x = p0.x * b0 + p1.x * b1 + p2.x * b2 + p3.x * b3;
    p.y = p0.y * b0 + p1.y * b1 + p2.y * b2 + p3.y * b3;
    p.z = p0.z * b0 + p1.z * b1 + p2.z * b2 + p3.z * b3;
    p.w = 1.f;

    return p;
}

void gfx::bezier_patch::generate() {
    vec4 vertex;
    vec4 q0, q1, q2, q3;
    vec4 r0, r1, r2, r3;
    vec3 tangent1, tangent2;
    float u = 0.f;
    float delta = 1.f / static_cast<float>(m_fidelity);
    float normal_delta = 0.0001f;

    for(size_t i = 0; i < m_fidelity; ++i) {
        float v = 0.f;
        q0 = eval_curve(u, m_controlpoints[0][0], m_controlpoints[0][1], m_controlpoints[0][2], m_controlpoints[0][3]);
        q1 = eval_curve(u, m_controlpoints[1][0], m_controlpoints[1][1], m_controlpoints[1][2], m_controlpoints[1][3]);
        q2 = eval_curve(u, m_controlpoints[2][0], m_controlpoints[2][1], m_controlpoints[2][2], m_controlpoints[2][3]);
        q3 = eval_curve(u, m_controlpoints[3][0], m_controlpoints[3][1], m_controlpoints[3][2], m_controlpoints[3][3]);

        r0 = eval_curve(u + normal_delta, m_controlpoints[0][0], m_controlpoints[0][1], m_controlpoints[0][2], m_controlpoints[0][3]);
        r1 = eval_curve(u + normal_delta, m_controlpoints[1][0], m_controlpoints[1][1], m_controlpoints[1][2], m_controlpoints[1][3]);
        r2 = eval_curve(u + normal_delta, m_controlpoints[2][0], m_controlpoints[2][1], m_controlpoints[2][2], m_controlpoints[2][3]);
        r3 = eval_curve(u + normal_delta, m_controlpoints[3][0], m_controlpoints[3][1], m_controlpoints[3][2], m_controlpoints[3][3]);

        for(size_t j = 0; j < m_fidelity; ++j) {
            vertex = eval_curve(v, q0, q1, q2, q3);
            tangent1 = (eval_curve(v + normal_delta, q0, q1, q2, q3) - vertex).to_vec3().normalize();
            tangent2 = (eval_curve(v, r0, r1, r2, r3) - vertex).to_vec3().normalize();
            m_normals[i][j] = tangent1.cross(tangent2).to_vec4(1.f);
            m_vertices[i][j] = vertex;
            m_texcoords[i][j] = vec3( i / (float) m_fidelity, j / (float) m_fidelity, 0.f);
            v += delta;
        }
        u += delta;
    }
}
