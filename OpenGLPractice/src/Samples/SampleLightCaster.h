#pragma once
#include "Sample.h"
#include "Camera.h"
#include "GameObject.h"
#include "Light.h"
#include "Material.h"

#include <memory>
#include <vector>

namespace Sample
{
    class SampleLightCaster : public Sample
    {
    private:
        std::unique_ptr<GameObject> dirCube;
        std::unique_ptr<GameObject> pointCube;
        std::unique_ptr<Camera> camera;
        std::unique_ptr<Light<DirLightProperties>> dirLight;
        std::unique_ptr<Light<PointLightProperties>> pointLight;
        LightType currentLightType = LightType::DIRECTIONAL;
        const char* lightTypes[2] = { "Points Light", "Directional Light"};

        void CreateCube(std::unique_ptr<GameObject> &cube, LightType type);
        
    public:
        SampleLightCaster();
        ~SampleLightCaster();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImguiRender() override;
    };
}