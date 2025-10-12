#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

#include <memory>



namespace Mesh
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
    };
    
    class Mesh
    {
    protected:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::unique_ptr<VertexArray> vertexArray;
        std::unique_ptr<VertexBuffer> vertexBuffer;
        std::unique_ptr<IndexBuffer> indexBuffer;

    public:
        Mesh() {}
        Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
            : vertices(vertices), indices(indices)
        {
            SetupMesh();
        }
        virtual ~Mesh() {}

        inline const VertexArray& GetVertexArray() const { return *vertexArray; }
        inline const IndexBuffer& GetIndexBuffer() const { return *indexBuffer; }

    protected:
        void SetupMesh()
        {
            vertexArray = std::make_unique<VertexArray>();
            vertexBuffer = std::make_unique<VertexBuffer>(vertices.data(), vertices.size() * sizeof(Vertex));
            VertexBufferLayout layout;
            layout.Push<float>(3); // position
            layout.Push<float>(3); // normal
            layout.Push<float>(2); // texture coordinate
            indexBuffer = std::make_unique<IndexBuffer>(indices.data(), indices.size());
            vertexArray->AddBuffer(*vertexBuffer, layout, *indexBuffer);

            vertexArray->Unbind();
            vertexBuffer->Unbind();
            indexBuffer->Unbind();
        }
    };
}