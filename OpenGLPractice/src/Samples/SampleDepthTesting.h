#pragma once

#include "Sample.h"
#include "Camera.h"
#include "GameObject.h"

#include <vector>
#include <memory>

namespace Sample
{
    class SampleDepthTesting : public Sample
    {
    private:
        std::vector<std::unique_ptr<GameObject>> cubes;
        std::unique_ptr<Camera> camera;
		bool depthTestEnabled = false;
		bool isLinerizedDepth = false;
		bool isCubeLeftSelected = true;

    public:
        SampleDepthTesting();
        ~SampleDepthTesting();
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImguiRender() override;
    };
}

