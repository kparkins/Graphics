#include "texture.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


//gfx::texture* gfx::texture::m_emptytexture = new gfx::texture();

gfx::texture::texture() {
    m_id = 0;
}

gfx::texture::~texture() {
    //
}

void gfx::texture::bind() {
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void gfx::texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

gfx::texture::texture(const string & filename) {
    int twidth, theight;   // texture m_width/m_height [pixels]
    unsigned char* tdata;  // texture pixel data

    //Load image file
    tdata = loadppm(filename.c_str(), twidth, theight);
    //tdata = SOIL_load_image(filename.c_str(), &twidth, &theight, 0, SOIL_LOAD_RGB);

    //If the image wasn't loaded, can't continue
    if(tdata == NULL) {
        std::cout << "Error loading image -- " << filename << std::endl;
        return;
    }
    this->generate(tdata, twidth, theight);
}
void gfx::texture::generate(unsigned char* data, int width, int height) {
    GLuint texture[1];     // storage for one texture
    //Create ID for texture
    glGenTextures(1, &texture[0]);
    m_id = texture[0];
    //Set this texture to be the one we are working with
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    //Generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    //Make sure no bytes are padded:
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    //Select GL_MODULATE to mix texture with quad m_color for shading:
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    //Use bilinear interpolation:
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //And unbind it!
    glBindTexture(GL_TEXTURE_2D, 0);
}


/** Load a ppm file from disk.
 @input m_filename The location of the PPM file.  If the file is not found, an error message
 will be printed and this function will return 0
 @input m_width This will be modified to contain the m_width of the loaded image, or 0 if file not found
 @input m_height This will be modified to contain the m_height of the loaded image, or 0 if file not found
 @return Returns the RGB pixel data as m_interleaved unsigned chars (R0 G0 B0 R1 G1 B1 R2 G2 B2 .... etc) or 0 if an error ocured
 **/
unsigned char* gfx::texture::loadppm(const char* filename, int& width, int& height) {
    const int BUFSIZE = 128;
    FILE* fp;
    size_t read;
    unsigned char* rawData;
    char buf[3][BUFSIZE];
    char* retval_fgets;
    size_t retval_sscanf;
    
    //Open the texture file
    if((fp = fopen(filename, "rb")) == NULL) {
        std::cerr << "error reading ppm file, could not locate " << filename << std::endl;
        width = 0;
        height = 0;
        return NULL;
    }
    
    //Read magic number:
    retval_fgets = fgets(buf[0], BUFSIZE, fp);
    
    //Read m_width and m_height:
    do {
        retval_fgets = fgets(buf[0], BUFSIZE, fp);
    } while(buf[0][0] == '#');
    
    //Set the m_width and m_height
    retval_sscanf=sscanf(buf[0], "%s %s", buf[1], buf[2]);
    width  = atoi(buf[1]);
    height = atoi(buf[2]);
    
    //Read maxval:
    do {
        retval_fgets=fgets(buf[0], BUFSIZE, fp);
    } while(buf[0][0] == '#');
    
    //Read image data:
    rawData = new unsigned char[width * height * 3];
    read = fread(rawData, width * height * 3, 1, fp);
    fclose(fp);
    
    //If the read was a failure, error
    if(read != 1) {
        std::cerr << "error parsing ppm file, incomplete data" << std::endl;
        delete[] rawData;
        width = 0;
        height = 0;
        return NULL;
    }
    return rawData;
}
