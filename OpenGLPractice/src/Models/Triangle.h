#pragma once

#include "Model.h"

namespace Model
{
    class Triangle : public Model
    {
    public:
        Triangle(float leftX, float rightX, float height) : Model()
        {
            float position[] =
            {
                               leftX, -height / 2, // 0
                              rightX, -height / 2, // 1
                (rightX + leftX) / 2,  height / 2  // 2
            };

            unsigned int indices[] =
            {
                0, 1, 2,
            };

            vertexArray = std::make_unique<VertexArray>();
            vertexBuffer = std::make_unique<VertexBuffer>(position, 2 * 3 * sizeof(float));
            VertexBufferLayout layout;
            layout.Push<float>(2); // position
            indexBuffer = std::make_unique<IndexBuffer>(indices, 3); // index buffer binding must be done after vertex buffer binding
            vertexArray->AddBuffer(*vertexBuffer, layout, *indexBuffer);
            
            vertexArray->Unbind();
            vertexBuffer->Unbind();
            indexBuffer->Unbind();
        };

        ~Triangle() {}
    };
} // namespace Model
