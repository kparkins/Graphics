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
    
    unsigned int m_id;
    static Texture* m_emptyTexture;
    
protected:
    
    const char*m_filename;
    
    static unsigned char* loadPPM(const char*, int&, int&);
    
};

#endif
