#include "window.h"

void gfx::window::initialize() {
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
            (*m_bezierpatch)[i][j] = vec4(i / 4.f, j / 4.f, (abs(i %2)) ? -1.f : 1.f, 1.f);
        }
    }
    for( int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            std::cout << (*m_bezierpatch)[i][j].x << " "
                      << (*m_bezierpatch)[i][j].y << " "
                      << (*m_bezierpatch)[i][j].z << " | ";
        }
        std::cout << std::endl;
    }
    /*
    (*m_bezierpatch)[0][0] = vec4(-.5f, .5f, 0.f, 1.f);
    (*m_bezierpatch)[1][0] = vec4(-.5f, .25f, 0.f, 1.f);
    (*m_bezierpatch)[2][0] = vec4(-.5f, -.25f, 0.f, 1.f);
    (*m_bezierpatch)[3][0] = vec4(-.5f, -.5f, 0.f, 1.f);

    (*m_bezierpatch)[0][1] = vec4(-.25f, .5f, -.5f, 1.f);
    (*m_bezierpatch)[1][1] = vec4(-.25f, .25f, -.5f, 1.f);
    (*m_bezierpatch)[2][1] = vec4(-.25f, -.25f, -.5f, 1.f);
    (*m_bezierpatch)[3][1] = vec4(-.25f, -.5f, -.5f, 1.f);

    (*m_bezierpatch)[0][2] = vec4(.25f, .5f, 0.f, 1.f);
    (*m_bezierpatch)[1][2] = vec4(.25f, .25f, 0.f, 1.f);
    (*m_bezierpatch)[2][2] = vec4(.25f, -.25f, 0.f, 1.f);
    (*m_bezierpatch)[3][2] = vec4(.25f, -.5f, 0.f, 1.f);

    (*m_bezierpatch)[0][3] = vec4(.5f, .5f, -0.5f, 1.f);
    (*m_bezierpatch)[1][3] = vec4(.5f, .25f, -0.5f, 1.f);
    (*m_bezierpatch)[2][3] = vec4(.5f, -.25f,-0.5f, 1.f);
    (*m_bezierpatch)[3][3] = vec4(.5f, -.5f, -0.5f, 1.f);
*/
    m_bezierpatch->generate();


    for(size_t i = 0; i < 4; ++i) {
        for(size_t j = 0; j < 4; ++j) {
            std::cout << std::setw(2) << (*m_bezierpatch)[j][i].x << " "
                      << std::setw(2) << (*m_bezierpatch)[j][i].y << " "
                      << std::setw(2) << (*m_bezierpatch)[j][i].z << " -- ";
        }
        std::cout << std::endl;
    }
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

    mat4 transform;
    mat4 scale;
    mat4 trans;
    mat4 rot;

    trans.translate(-.5f, -.5f, 0.f);
    rot.rotatez(M_PI * -90.f/ 180.f);
    scale.scale(5.f);

    transform = scale * rot * trans;

    m_directlight->bind();
    m_pointlight->bind();
    m_skybox.draw(m_skyboxtrans);
    m_bezierpatch->draw(transform);
    m_scene->draw(m_worldscale);
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void gfx::window::keycb(unsigned char key, int x, int y) {

}

void gfx::window::specialkeycb(int key, int x, int y) {

}

void gfx::window::mousebuttoncb(int button, int state, int x, int y) {

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
