#pragma once
#include "Sample.h"
#include "Camera.h"
#include "GameObject.h"
#include "Light.h"
#include "Material.h"

#include <memory>

namespace Sample
{
    class SampleLightCaster : public Sample
    {
    private:
        std::unique_ptr<GameObject> cube;
        std::unique_ptr<Camera> camera;
        std::unique_ptr<Light<DirLightProperties>> dirLight;
        
    public:
        SampleLightCaster();
        ~SampleLightCaster();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImguiRender() override;
    };
}