#pragma once

#include "Sample.h"
#include "Camera.h"
#include "GameObject.h"

#include "imgui/imgui.h"

#include <memory>

namespace Sample
{
    class SampleLightTest :
        public Sample
    {
    private:
        std::unique_ptr<GameObject> ligthBall;
        std::unique_ptr<GameObject> cube;
        std::unique_ptr<Camera> camera;

        ImVec2 lastMousePos;
        bool isShowCursor = false;

    public:
        SampleLightTest();
        ~SampleLightTest();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImguiRender() override;
    };
}

