#pragma once

#include "Model.h"

namespace Model
{
    class Rectangle : public Model
    {
    public:
        Rectangle(float width, float height, float coordX, float coordY) : Model()
        {
            float position[] = 
            {
                -width / 2, -height / 2, 0,      0,     // 0
                 width / 2, -height / 2, coordX, 0,     // 1
                 width / 2,  height / 2, coordX, coordY // 2
                -width / 2,  height / 2, 0,      coordY // 3
            };

            unsigned int indices[] =
            {
                0, 1, 2,
                2, 3, 0
            };

            vertexArray = std::make_unique<VertexArray>();
            vertexBuffer = std::make_unique<VertexBuffer>(position, 4 * 4 * sizeof(float));
            VertexBufferLayout layout;
            layout.Push<float>(2); // position
            layout.Push<float>(2); // texture coordinate
            vertexArray->AddBuffer(*vertexBuffer, layout);
            indexBuffer = std::make_unique<IndexBuffer>(indices, 6); // index buffer binding must be done after vertex buffer binding
            
            vertexArray->Unbind();
            vertexBuffer->Unbind();
            indexBuffer->Unbind();
        };

        ~Rectangle();
    };
} // namespace name

