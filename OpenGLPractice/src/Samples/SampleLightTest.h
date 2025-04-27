#pragma once

#include "Sample.h"
#include "Camera.h"
#include "GameObject.h"
#include "Light.h"
#include "glm/glm.hpp"
#include "MaterialDatabase.h"

#include <memory>

namespace Sample
{
    class SampleLightTest :
        public Sample
    {
    private:
        std::unique_ptr<GameObject> cube;
        std::unique_ptr<Camera> camera;
		std::unique_ptr<Light> light;

		glm::vec3 lightStrength;
        MaterialProperties currentMaterial;
        MaterialDatabase database;

        void UpdatCubeMaterial();

    public:
        SampleLightTest();
        ~SampleLightTest();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImguiRender() override;
    };
}

