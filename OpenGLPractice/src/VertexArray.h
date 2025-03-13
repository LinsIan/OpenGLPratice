#pragma once

#include <VertexBuffer.h>

class VertexArray
{
private:
    /* data */
public:
    VertexArray(/* args */);
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void Bind() const;
};


