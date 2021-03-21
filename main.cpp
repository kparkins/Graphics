#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "grid.h"
#include "window.h"

static gfx::window_ptr main_window;

static void display() {
    main_window->displaycb();
}

static void reshape(int x, int y) {
    main_window->reshapecb(x, y);
}

static void idle() {
    main_window->idlecb();
}

static void key(unsigned char key, int x, int y) {
    main_window->keycb(key, x, y);
}

static void specialkey(int key, int x, int y) {
    main_window->specialkeycb(key, x, y);
}

static void mousebutton(int button, int state, int x, int y) {
    main_window->mousebuttoncb(button, state, x, y);
}

int main(int argc, char *argv[]) {
    main_window = make_shared<gfx::window>();
    main_window->height(512);
    main_window->width(512);
    //GLUT and OpenGL Configuration
    glutInit(&argc, argv);                                      //Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   //Open an OpenGL context with double buffering, RGB colors, and depth buffering

    glutInitWindowSize(main_window->width(), main_window->height());          //Set initial window m_size
    glutCreateWindow("cube"); //Open window and set window title
    
    glEnable(GL_DEPTH_TEST);                                    //Enable depth buffering
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);                               //Clear depth buffer
    glClearColor(0.0, 0.0, 0.0, 0.0);                           //Set clear m_color to black
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);                  //Set polygon drawing mode to fill front and back of each polygon
    glDisable(GL_CULL_FACE);                                    //Disable backface culling to render both sides of polygons
    glShadeModel(GL_SMOOTH);                                    //Set shading to smooth
    
    //glEnable(GL_COLOR_MATERIAL);                                //Enable m_color materials
    glEnable(GL_LIGHTING);                                      //Enable lighting
    glEnable(GL_NORMALIZE);                                     //Auto normalize surface normals
    glEnable(GL_TEXTURE_2D);                                    //Enable 2D textures
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);        //Enable Local Viewer light Model
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    //Register callback functions:
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutKeyboardFunc(key);
    glutSpecialFunc(specialkey);
    glutMouseFunc(mousebutton);
    //Print Shader Debug Information:
    printf("%s\n%s\n",
           glGetString(GL_RENDERER),  // e.g. Intel HD Graphics 3000 OpenGL Engine
           glGetString(GL_VERSION)    // e.g. 3.2 INTEL-8.0.61
           );
   

    gfx::grid<int> grid(4, 4);
    for(int i = 0; i < 4; ++i) {
        for( int j = 0; j < 4; ++j) {
            grid[i][j] = 4 * i + j;
        }
    }

    for(int i = 0; i < 4; ++i) {
        for( int j = 0; j < 4; ++j) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }

    main_window->initialize();
    glutMainLoop();
    main_window.reset();

    return 0;
}
