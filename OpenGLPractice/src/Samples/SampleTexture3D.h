#pragma once

#include "Sample.h"
#include "Renderer.h"
#include "Cube.h"
#include "Material.h"
#include "Camera.h"
#include "imgui/imgui.h"

#include <memory>
#include <vector>

namespace Sample
{
    class SampleTexture3D : public Sample
    {
    private:
		std::unique_ptr<Renderer> renderer;
		std::unique_ptr<Material> material;
		std::vector<std::unique_ptr<Model::Cube>> cubes;
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
