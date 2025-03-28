#pragma once
#include "Sample.h"
#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <memory>

namespace Sample
{
    class SamplePolygonTriangle : public Sample
    {
    private:
        std::unique_ptr<Renderer> renderer;
        std::unique_ptr<Shader> shader;
        std::unique_ptr<VertexArray> vertexArrayA;
        std::unique_ptr<VertexArray> vertexArrayB;
        std::unique_ptr<VertexBuffer> vertexBufferA;
        std::unique_ptr<VertexBuffer> vertexBufferB;
        std::unique_ptr<IndexBuffer> indexBufferA;
        std::unique_ptr<IndexBuffer> indexBufferB;

    public:
        SamplePolygonTriangle();
        ~SamplePolygonTriangle();

        void OnRender() override;
    };
}

