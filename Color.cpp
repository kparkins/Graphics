#include "Color.h"
#include <iostream>
#include <cstdlib>
#include <string.h>

#define clampf(min,max,num) (num < min ? min : num > max ? max : num)


Color::Color(void) {
    u8bit = 0xFF;
    memset(static_cast<void*>(&r), 1.f, sizeof(float) * 4);
}

Color::Color(float r, float g, float b) {
    u8bit = 0xFF;
    memset(static_cast<void*>(&r), 1.f, sizeof(float) * 4);
    a = 1.f;
}

Color::Color(float r, float g, float b, float a) {
    u8bit = 0xFF;
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

Color::Color(unsigned int hex) {
    u8bit = 0xFF;
    //construct a bit mask 0xff000000
    unsigned int mask = 0xff << 0x18;
    
    //Unpack each 8bit segment into a float, and normalize such that 255 ~= 1.0
    for(int i = 0; mask; ++i, mask >>= 0x8) {
        (&r)[i] = ((float) ((hex & mask) >> ((3 - i) * 0x8))) / u8bit;
    }
}

Color::~Color() {
    //Delete any dynamically allocated memory/objects here
}


float* Color::ptr(void) {
    //Returns a pointer to the m_color array
    return &r;
}

float& Color::operator [] (int i) {
    //Returns a reference to the specified element
    return (&r)[i];
}

Color Color::interpolate(Color& c1, float t) {
    t = static_cast<float>(clampf(0.0, 1.0, t));
    return Color((1.f - t) * r + t * c1[0],
                 (1.f - t) * g + t * c1[1],
                 (1.f - t) * b + t * c1[2],
                 (1.f - t) * a + t * c1[3]);
}

Color Color::red(void) {
    return Color(0xff0000ff);
}

Color Color::blue(void) {
    return Color(0x0000ffff);
}

Color Color::green(void) {
    return Color(0x00ff00ff);
}

Color Color::yellow(void) {
    return Color(0xffff00ff);
}

Color Color::orange(void) {
    return Color(0xff8800ff);
}

Color Color::purple(void) {
    return Color(0xff00ffff);
}

Color Color::white(void) {
    return Color(0xffffffff);
}

Color Color::black(void) {
    return Color(0x00000000);
}

Color Color::lightBrown(void) {
    return Color(0xFFCCAAFF);
}

Color Color::randomPastel(void) {
    unsigned int color =
        ((0x50 + (static_cast<unsigned int>(rand()) % 128)) << 0x18) +
        ((0x50 + (static_cast<unsigned int>(rand()) % 128)) << 0x10) +
        ((0x50 + (static_cast<unsigned int>(rand()) % 128)) << 0x08) +
        0xFF;
    
    return Color(color);
}

Color Color::randomDarkPastel(void) {
    unsigned int color =
        ((0x10 + (static_cast<unsigned int>(rand()) % 128)) << 0x18) +
        ((0x10 + (static_cast<unsigned int>(rand()) % 128)) << 0x10) +
        ((0x10 + (static_cast<unsigned int>(rand()) % 128)) << 0x08) +
        0xFF;
    
    return Color(color);
}

Color Color::randomBrightPastel(void) {
    unsigned int color =
        ((0x10 + (static_cast<unsigned int>(rand()) % 200)) << 0x18) +
        ((0x10 + (static_cast<unsigned int>(rand()) % 200)) << 0x10) +
        ((0x10 + (static_cast<unsigned int>(rand()) % 200)) << 0x08) +
        0xFF;
    
    return Color(color);
}

Color Color::randomDarkShade(void) {
    unsigned int shade = 0x0 + (rand() % 80);
    
    unsigned int color =
        (shade << 0x18) +
        (shade << 0x10) +
        (shade << 0x08) +
        0xFF;
    
    return Color(color);
}

Color Color::ambientDefault(void) {
    return Color(0x111111FF);
}

Color Color::diffuseDefault(void) {
    return Color(0xffffffFF);
}

Color Color::specularDefault(void) {
    return Color(0xffffffFF);
}

Color Color::ambientMaterialDefault(void) {
    return Color(0x434343FF);
}

Color Color::diffuseMaterialDefault(void) {
    return Color(0xbcbcbcFF);
}

Color Color::specularMaterialDefault(void) {
    return Color(0xffffffFF);
}

Color Color::emissionMaterialDefault(void) {
    return Color(0x000000FF);
}

