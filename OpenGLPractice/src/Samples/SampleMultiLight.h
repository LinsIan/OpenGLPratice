#pragma once
#include "Sample.h"
#include "Light.h"
#include "Camera.h"
#include "Material.h"
#include "GameObject.h"

#include <memory>

namespace Sample
{
    class SampleMultiLight :
        public Sample
    {
    private:
        std::unique_ptr<Camera> camera;
        std::unique_ptr<Light> dirLight;
        std::unique_ptr<GameObject> cube;

    public:
        SampleMultiLight();
        ~SampleMultiLight();
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImguiRender() override;
    };
}

