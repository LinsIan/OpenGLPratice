#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

#include <memory>
#include <vector>

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
        std::shared_ptr<VertexArray> vertexArray;
        std::shared_ptr<VertexBuffer> vertexBuffer;
        std::shared_ptr<IndexBuffer> indexBuffer;

    public:
        Mesh() {}
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, bool setup = true)
            : vertices(std::move(vertices)), indices(std::move(indices))
        {
            if (setup)
                SetupMesh();
        }
        virtual ~Mesh() {}
        
        inline std::vector<Vertex>& GetVertices() { return vertices; }
        inline std::vector<unsigned int>& GetIndices() { return indices; }
        inline const VertexArray& GetVertexArray() const { return *vertexArray; }
        inline const IndexBuffer& GetIndexBuffer() const { return *indexBuffer; }

    public:
        void SetupMesh()
        {
            vertexArray = std::make_shared<VertexArray>();
            vertexBuffer = std::make_shared<VertexBuffer>(vertices.data(), vertices.size() * sizeof(Vertex));
            VertexBufferLayout layout;
            layout.Push<float>(3); // position
            layout.Push<float>(3); // normal
            layout.Push<float>(2); // texture coordinate
            indexBuffer = std::make_shared<IndexBuffer>(indices.data(), indices.size());
            vertexArray->AddBuffer(*vertexBuffer, layout, *indexBuffer);

            vertexArray->Unbind();
            vertexBuffer->Unbind();
            indexBuffer->Unbind();
        }
    };
}