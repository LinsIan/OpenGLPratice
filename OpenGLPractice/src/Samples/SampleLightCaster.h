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
		std::unique_ptr<GameObject> spotCube;
        std::unique_ptr<Camera> camera;
        std::unique_ptr<Light<DirLightProperties>> dirLight;
        std::unique_ptr<Light<PointLightProperties>> pointLight;
		std::unique_ptr<Light<SpotLightProperties>> spotLight;
        LightType currentLightType = LightType::DIRECTIONAL;
        const char* lightTypes[3] = { "Points Light", "Directional Light", "Spot Light"};

        void CreateCube(std::unique_ptr<GameObject> &cube, LightType type);
		void RotateCube(GameObject &cube, float deltaTime);
        
    public:
        SampleLightCaster();
        ~SampleLightCaster();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImguiRender() override;
    };
}