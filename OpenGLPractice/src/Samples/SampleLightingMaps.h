#pragma once

#include "Sample.h"
#include "Camera.h"
#include "GameObject.h"
#include "Material.h"

#include <memory>

namespace Sample
{
    class SampleLightingMaps : public Sample
    {
    private:
        std::unique_ptr<Camera> camera;
        std::unique_ptr<GameObject> ligthBall;
        std::unique_ptr<GameObject> cube;

        void UpdateCubeMaterial();

    public:
        SampleLightingMaps();
        ~SampleLightingMaps();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImguiRender() override;
    };
}

