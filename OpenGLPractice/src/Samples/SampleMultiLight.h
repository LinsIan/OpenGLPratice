#pragma once
#include "Sample.h"
#include "Light.h"
#include "Camera.h"
#include "Material.h"
#include "GameObject.h"

#include <memory>
#include <vector>

namespace Sample
{
    class SampleMultiLight :
        public Sample
    {
    private:
        std::unique_ptr<Camera> camera;
        std::unique_ptr<Light<DirLightProperties>> dirLight;
        std::vector<std::unique_ptr<Light<PointLightProperties>>> pointLights;
        std::unique_ptr<Light<SpotLightProperties>> spotLight;
        std::vector<std::unique_ptr<GameObject>> cubes;

    public:
        SampleMultiLight();
        ~SampleMultiLight();
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImguiRender() override;
    };
}

