#pragma once
#include "Renderer.h"

class UniformBuffer
{
private:
    unsigned int rendererID;

public:
    UniformBuffer(unsigned int size, unsigned int bindingPoint)
    {
        GLCall(glGenBuffers(1, &rendererID));
        Bind();
        GLCall(glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));
        GLCall(glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, rendererID));
        Unbind();
    }

    ~UniformBuffer()
    {
        GLCall(glDeleteBuffers(1, &rendererID));
    }                     
    void Bind() const
    {
        GLCall(glBindBuffer(GL_UNIFORM_BUFFER, rendererID));
    }
    
    void Unbind() const
    {
        GLCall(glBindBuffer(GL_UNIFORM_BUFFER, 0));
    }
    void SetData(unsigned int offset, unsigned int size, const void* data) const
    {
        Bind();
        GLCall(glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data));
        Unbind();
    }
        
};