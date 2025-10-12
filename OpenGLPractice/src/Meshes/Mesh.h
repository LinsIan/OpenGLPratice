#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

#include <memory>



namespace Mesh
{
    class Mesh
    {
    protected:
        std::unique_ptr<VertexArray> vertexArray;
        std::unique_ptr<VertexBuffer> vertexBuffer;
        std::unique_ptr<IndexBuffer> indexBuffer;

    public:
        Mesh() {}
        virtual ~Mesh() {}

        inline const VertexArray& GetVertexArray() const { return *vertexArray; }
        inline const IndexBuffer& GetIndexBuffer() const { return *indexBuffer; }
    };
} // namespace Model