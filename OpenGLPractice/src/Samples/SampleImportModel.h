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
    class SampleImportModel :
        public Sample
    {
    private:
        std::unique_ptr<Camera> camera;
        std::unique_ptr<Light<DirLightProperties>> dirLight;

    public:
        SampleImportModel();
        ~SampleImportModel();
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImguiRender() override;
    };
}

