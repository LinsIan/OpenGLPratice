#pragma once

#include "Sample.h"
#include "Camera.h"
#include "GameObject.h"
#include "Light.h"
#include "Material.h"

#include <memory>

namespace Sample
{
    class SampleLightingMaps : public Sample
    {
    private:
        std::unique_ptr<Camera> camera;
		std::unique_ptr<Light> light;
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

