#pragma once

#include "Renderer.h"

class Texture
{
private:
    unsigned int rendererID;
    std::string filePath;
    unsigned char* localBuffer;
    int width;
    int height;
    int bitPerPixel;
public:
    Texture(const std::string& path);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void UnBind() const;

    inline int GetWidth() const { return width; }
    inline int GetHeight() const { return height; }
};
