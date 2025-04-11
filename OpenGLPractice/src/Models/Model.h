#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

#include <memory>



namespace Model
{
    class Model
    {
    protected:
        std::unique_ptr<VertexArray> vertexArray;
        std::unique_ptr<VertexBuffer> vertexBuffer;
        std::unique_ptr<IndexBuffer> indexBuffer;

    public:
        Model() {}
        virtual ~Model() {}

        inline const VertexArray& GetVertexArray() const { return *vertexArray; }
        inline const IndexBuffer& GetIndexBuffer() const { return *indexBuffer; }
    };
} // namespace Model