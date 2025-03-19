#pragma once
#include <GL/glew.h>
#include <vector>
#include "Renderer.h"

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT: return sizeof(GLfloat);
            case GL_UNSIGNED_INT: return sizeof(GLuint);
            case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
        }

        ASSERT(false);
        return 0;
    }

    VertexBufferElement(unsigned int type, unsigned int count, bool normalized)
        : type(type), count(count), normalized(normalized) {};
};


class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> elements;
    unsigned int stride;

public:
    VertexBufferLayout() : stride(0) {};

    template<typename T>
    void Push(unsigned int count)
    {
        ASSERT(false);
    }

    template<>
    void Push<float>(unsigned int count)
    {
        elements.push_back({ GL_FLOAT, count, GL_FALSE });
        stride += count * sizeof(GLfloat);
    }

    template<>
    void Push<unsigned int>(unsigned int count)
    {
        elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
        stride += count * sizeof(GLuint);
    }

    template<>
    void Push<unsigned char>(unsigned int count)
    {
        elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
        stride += count * sizeof(GLubyte);
    }

    inline const std::vector<VertexBufferElement> GetElements() const { return elements; }
    inline unsigned int GetStride() const { return stride; }
};
