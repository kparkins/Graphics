#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <string>

class Texture {
    
public:

    
    Texture(void);
    Texture(const char* filename);
    virtual ~Texture(void);
    
    void bind(void);
    void unbind(void);
    
    unsigned int id;
    static Texture* emptyTexture;
    
protected:
    
    const char* filename;
    
    static unsigned char* loadPPM(const char*, int&, int&);
    
};

#endif
