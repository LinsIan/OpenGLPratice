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

void Renderer::Clear()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const Shader& shader, const unsigned int indexCount)
{
    shader.Bind();
    va.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr));
}

void Renderer::SetPolygonMode(GLenum mode)
{
    GLCall(glPolygonMode(GL_FRONT_AND_BACK, mode));
}
