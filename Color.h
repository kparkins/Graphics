#ifndef COLOR_H
#define COLOR_H

#include "Macros.h"

class Color {

    
public:
    
    Color(void);
    Color(float r, float g, float b);
    Color(float r, float g, float b, float a);
    Color(unsigned int hex);
    
    ~Color(void);
    
    float* ptr(void);
    float& operator [] (int);
    
    //Mathematical operations on colors
    Color interpolate(Color&, float);

    //Pre-Defined Colors
    static Color red(void);
    static Color blue(void);
    static Color green(void);
    static Color yellow(void);
    static Color orange(void);
    static Color purple(void);
    static Color white(void);
    static Color black(void);
    static Color lightBrown(void);
    
    //Randomized Colors
    static Color randomPastel(void);
    static Color randomDarkPastel(void);
    static Color randomBrightPastel(void);
    static Color randomDarkShade(void);
    
    //Used by Light
    static Color ambientDefault(void);
    static Color diffuseDefault(void);
    static Color specularDefault(void);
    
    //Used by Material
    static Color ambientMaterialDefault(void);
    static Color diffuseMaterialDefault(void);
    static Color specularMaterialDefault(void);
    static Color emissionMaterialDefault(void);

#if defined(__GNUC__) | defined(__clang__)
    struct {
        float r, g, b, a;
    }ALIGN_16;
#elif defined(_MSC_VER)
    ALIGN_16 struct {
        float r, g, b, a;
    };
#endif

protected:

    unsigned char u8bit;
    
};

#endif
