#include "Renderer.h"
#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR) {}
}

bool GLCheckError(const char* funcName, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "): " << funcName << " "
            << file << ":" << line << std::endl;
        return true;
    }

    return false;
}