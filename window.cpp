#include "window.h"

float calculate_z(int j) {
    j = abs(j);
    if (j == 1) {
        return 1.f;
    } else if(j == 2) {
        return -1.f;
    }
    return 0.f;
}

void gfx::window::initialize() {
    m_time = 0.f;
    m_prev = vec3(0.f, 0.f, 20.f);
    m_camera = make_shared<camera>();
    m_sphere = make_shared<sphere>(.1f, 1500, 1500);
    m_cube = make_shared<cube>(1.f);
    m_scene = make_shared<group>();
    m_directlight = make_shared<light>();
    m_pointlight = make_shared<light>();
    m_bezierpatch = make_shared<bezier_patch>(100);

    texture_ptr logo = make_shared<texture>("img/Ucsd-logo.ppm");
    m_bezierpatch->texture(logo);
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            (*m_bezierpatch)[i][j] = vec4(i / 4.f, j / 4.f, 0.f, 1.f);
        }
    }

    m_bezierpatch->generate();

    mat4 scale;
    mat4 trans;
    mat4 rot;

    trans.translate(-.5f, -.5f, 0.f);
    rot.rotatez(M_PI * -90.f/ 180.f);
    scale.scale(10.f);

    m_beziertrans = scale * rot * trans;

    vector<string> skybox_images(6);
    skybox_images[skybox::LEFT] = "img/sorbin/left.ppm";
    skybox_images[skybox::FRONT] = "img/sorbin/front.ppm";
    skybox_images[skybox::RIGHT] = "img/sorbin/right.ppm";
    skybox_images[skybox::BACK] = "img/sorbin/back.ppm";
    skybox_images[skybox::TOP] = "img/sorbin/top.ppm";
    skybox_images[skybox::BOTTOM] = "img/sorbin/bottom.ppm";
    m_skybox.load(skybox_images);
    m_skyboxtrans.scale(50.f);

    m_pointlight->directional(true);
    m_pointlight->angle(180.f);
    m_pointlight->position(vec4(0.f, 0.f, 10.f, 1.f));

    m_worldscale.identity();
}

void gfx::window::idlecb() {
    frame++;
    time = glutGet(GLUT_ELAPSED_TIME);
        this->update(time - timebase);
    int fps;
    if (time - timebase > 1000) {
        fps = frame * 1000.0 / (time - timebase);
        timebase = time;
        frame = 0;
        std::cout << "fps\t" << fps << std::endl;
    }
    displaycb();
}

void gfx::window::reshapecb(int w, int h) {
    m_width = w;                                                       //Set the window m_width
    m_height = h;                                                      //Set the window m_height
    glViewport(0, 0, w, h);                                          //Set new viewport m_size
    glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
    glLoadIdentity();                                                //Clear the projection matrix by loading the identity
    gluPerspective(60.0, double(m_width)/(double) m_height, 1.0, 1000.0); //Set perspective projection viewing frustum
}

void gfx::window::displaycb() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadMatrixf(m_camera->inverse_matrix().ptr());

    m_pointlight->bind();
    m_skybox.draw(m_skyboxtrans);
    m_bezierpatch->draw(m_beziertrans);

    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void gfx::window::update(float dt) {
    m_time += dt / 100000.f;
    for(int i = 0; i < 4; ++i) {
        (*m_bezierpatch)[i][1].z = cosf(m_time);
        (*m_bezierpatch)[i][2].z = cosf(m_time - (M_PI * 90.f / 180.f));
        (*m_bezierpatch)[i][3].z = cosf(m_time - (M_PI * 180.f / 180.f));

    }
    m_bezierpatch->generate();
}

void gfx::window::move_camera(gfx::mat4 & m) {
    vec3 e = m_camera->e();
    vec3 d = m_camera->d();
    vec3 up = m_camera->up();

    e = m * e;
    up = m * up;
    m_camera->set(e, d, up);
    reshapecb(m_width, m_height);
}

void gfx::window::keycb(unsigned char key, int x, int y) {
    mat4 scale;
    switch(key) {
        case 's':
            scale.scale(.9f);
            m_worldscale = m_worldscale * scale;
            m_beziertrans = m_beziertrans * scale;
            m_skyboxtrans = m_skyboxtrans * scale;
            break;
        case 'S':
            scale.scale(1.1f);
            m_worldscale = m_worldscale * scale;
            m_beziertrans = m_beziertrans * scale;
            m_skyboxtrans = m_skyboxtrans * scale;
            break;
        default:
            break;
    }
}

void gfx::window::specialkeycb(int key, int x, int y) {
    mat4 trans;
    switch (key) {
        case GLUT_KEY_UP:
            trans.rotatex(.05f);
            move_camera(trans);
            break;
        case GLUT_KEY_DOWN:
            trans.rotatex(-.05f);
            move_camera(trans);
            break;
        case GLUT_KEY_LEFT:
            trans.rotatey(.05f);
            move_camera(trans);
            break;
        case GLUT_KEY_RIGHT:
            trans.rotatey(-.05f);
            move_camera(trans);
            break;
        default:
            break;
    }
}

void gfx::window::mousebuttoncb(int button, int state, int x, int y) {

}

void gfx::window::mousemotioncb(int x, int y) {
   /* mat4 rot;
    vec3 e = m_camera->e();
    vec3 d = m_camera->d();
    vec3 up = m_camera->up();
    vec3 curr = this->convert_coords(x, y);
    vec3 axis = m_prev.cross(curr);
    float angle = acosf(curr.dot(m_prev) / (curr.magnitude() * m_prev.magnitude()));

    if(angle < 0.0001f) {
        return;
    }

    rot.rotate_arbitrary(axis, angle);
    e = rot * e;
    up = rot * up;
    m_camera->set(e, d, up);
    m_prev = curr;*/
}

gfx::vec3 gfx::window::convert_coords(int x, int y) {
    vec3 v;
    v.x = (2.f * x - m_width) / m_width;
    v.y = (m_height - 2.f * y) / m_height;
    v.z = 0.f;
    float distance = v.magnitude();
    if(distance > 1.f) {
        distance = 1.f;
    }
    v.z = sqrtf(1.f - (distance * distance));
    v.normalize();
    return v;
}

int gfx::window::width() {
    this->m_width;
}

int gfx::window::height() {
    return this->m_height;
}

void gfx::window::width(int w) {
    assert(w > 0);
    this->m_width = w;
}

void gfx::window::height(int h) {
    assert(h > 0);
    this->m_height = h;
}
