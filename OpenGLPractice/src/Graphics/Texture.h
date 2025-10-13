#pragma once

#include "Renderer.h"

class Texture
{
private:
    unsigned int rendererID;
    std::string filePath;
    std::string typeName;
    unsigned char* localBuffer;
    int width;
    int height;
    int bitPerPixel;
    int filteringMode;
    int wrappingMode;
public:
    Texture(const std::string& path, const std::string& typeName = "", int filtering = GL_LINEAR, int wrapping = GL_CLAMP_TO_EDGE);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void UnBind() const;

    inline int GetWidth() const { return width; }
    inline int GetHeight() const { return height; }
	inline void SetFilteringMode(int mode) { filteringMode = mode; }
	inline void SetWrappingMode(int mode) { wrappingMode = mode; }
    inline std::string GetFilePath() const { return filePath; }
};
