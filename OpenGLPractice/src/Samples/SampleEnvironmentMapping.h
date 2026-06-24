#pragma once
#include "Sample.h"
#include "GameObject.h"
#include "Skybox.h"
#include "Camera.h"

#include <vector>
#include <memory>


namespace Sample
{
    class SampleEnvironmentMapping : public Sample
    {
    private:
        std::unique_ptr<GameObject> reflectionCube;
        std::unique_ptr<GameObject> refractionCube;
        std::unique_ptr<Skybox> skybox;
        std::unique_ptr<Camera> camera;

    public:
        SampleEnvironmentMapping();
        ~SampleEnvironmentMapping();
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImguiRender() override;
    };
}
