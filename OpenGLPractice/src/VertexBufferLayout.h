#pragma once
#include <vector>
#include <GL/glew.h>

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    bool normalized;
};


class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> elements;

public:
    VertexBufferLayout()
    {
    }

    template<typename T>
    void Push(int count)
    {
        static_assert(false);
    }

    template<>
    void Push<float>(int count, bool normalized )
    {
        elements.push_back({ GL_FLOAT, count, normalized });
    }
};
