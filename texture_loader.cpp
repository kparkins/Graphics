#include "texture_loader.h"

gfx::texture_loader::texture_loader() {

}

gfx::texture_loader::~texture_loader() {

}

gfx::texture_ptr gfx::texture_loader::load(const string &filename, unsigned int format) {
    SOIL_load_OGL_texture("images/desertSkybox.ppm", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
}