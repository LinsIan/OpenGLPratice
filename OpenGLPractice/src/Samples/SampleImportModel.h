#pragma once
#include "Sample.h"
#include "Light.h"
#include "Camera.h"
#include "Material.h"
#include "Skybox.h"
#include "Model.h"

#include <memory>
#include <vector>

using std::unique_ptr;
using std::vector;
using std::shared_ptr;

namespace Sample
{
    class SampleImportModel :
        public Sample
    {
    private:
        std::unique_ptr<Camera> camera;
        std::unique_ptr<Skybox> skybox;
        std::unique_ptr<Light<DirLightProperties>> dirLight;
        std::unique_ptr<Light<PointLightProperties>> pointLight;
        std::unique_ptr<Light<SpotLightProperties>> spotLight;
        std::unique_ptr<Model> backpackModel;
        std::unique_ptr<GameObject> window;

    public:
        SampleImportModel();
        ~SampleImportModel();
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImguiRender() override;
    };
}

