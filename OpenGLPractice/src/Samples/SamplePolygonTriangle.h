#pragma once
#include "Sample.h"
#include "GameObject.h"

#include <memory>

namespace Sample
{
    class SamplePolygonTriangle : public Sample
    {
    private:
        std::unique_ptr<GameObject> triangleA;
        std::unique_ptr<GameObject> triangleB;
        std::unique_ptr<Renderer> renderer;

    public:
        SamplePolygonTriangle();
        ~SamplePolygonTriangle();

        void OnRender() override;
    };
}

