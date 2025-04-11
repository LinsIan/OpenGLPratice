#pragma once

#include "Sample.h"
#include "Camera.h"
#include "GameObject.h"
#include "imgui/imgui.h"

#include <memory>
#include <vector>

namespace Sample
{
    class SampleTexture3D : public Sample
    {
    private:
		std::vector<std::unique_ptr<GameObject>> cubes;
		std::unique_ptr<Camera> camera;

        ImVec2 lastMousePos;
        bool isShowCursor = false;

	public:
		SampleTexture3D();
		~SampleTexture3D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImguiRender() override;

    };
}
