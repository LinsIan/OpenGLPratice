#pragma once
#include "Sample.h"
#include "Renderer.h"
#include "Shader.h"
#include "Triangle.h"

#include <memory>

namespace Sample
{
    class SamplePolygonTriangle : public Sample
    {
    private:
        std::unique_ptr<Renderer> renderer;
        std::unique_ptr<Shader> shader;
        std::unique_ptr<Model::Triangle> triangleA;
        std::unique_ptr<Model::Triangle> triangleB;

    public:
        SamplePolygonTriangle();
        ~SamplePolygonTriangle();

        void OnRender() override;
    };
}

