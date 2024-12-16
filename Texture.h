#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include "CommonValues.h"

class Texture {
public:
    Texture();
    Texture(const char* fileLoc);

    bool LoadTexture();
    bool LoadTextureA();

    void UseTexture() const;
    void ClearTexture();

    ~Texture();
private:
    GLuint textureID;
    int width, height, bitDepth;

    const char *fileLocation;
};

#endif //TEXTURE_H
