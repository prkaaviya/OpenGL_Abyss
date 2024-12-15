#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include "stb_image.h"

class Texture {
public:
    Texture();
    Texture(char* fileLoc);

    bool LoadTexture();
    bool LoadTextureA();
    void UseTexture();
    void ClearTexture();

    ~Texture();
private:
    GLuint textureID;
    int width, height, bitDepth;

    char *fileLocation;
};

#endif //TEXTURE_H
