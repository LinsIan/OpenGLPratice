#include "SampleDepthTesting.h"
#include "Cube.h"
#include "UIManager.h"

namespace Sample
{
	SampleDepthTesting::SampleDepthTesting()
	{
		auto material = std::make_shared<Material>("res/shaders/DepthTest.shader");
		material->AddTexture("res/textures/container.jpg", 0, "u_Texture");
		material->BindTextures();
		material->GetShader().SetUniform1f("u_Degree", 0.8f);

		auto cube1 = std::make_unique<GameObject>(std::make_shared<Mesh::Cube>(0.1f, 1.2f, 1.2f), material);
		auto cube2 = std::make_unique<GameObject>(std::make_shared<Mesh::Cube>(1.2f, 1.2f, 1.2f), material);
		auto cube3 = std::make_unique<GameObject>(std::make_shared<Mesh::Cube>(0.6f, 0.8f, 1.4f), material);

		cubes.push_back(std::move(cube1));
		cubes.push_back(std::move(cube2));
		cubes.push_back(std::move(cube3));

		cubes[1]->GetTransform().SetTranslation(-2.6f, 0, -5.8f);
		cubes[1]->GetTransform().SetRotation(30, 34, -13);

		cubes[2]->GetTransform().SetTranslation(2.6f, 0, -2.6f);
		cubes[2]->GetTransform().SetRotation(-38, 60, 34);

		camera = std::make_unique<Camera>(CameraType::PERSPECTIVE, 960.0f, 540.0f);
	}

	SampleDepthTesting::~SampleDepthTesting()
	{
	}

	void SampleDepthTesting::OnUpdate(float deltaTime)
	{
		cubes[1]->GetTransform().GetRotation().y += 10 * deltaTime;
		cubes[2]->GetTransform().GetRotation().x += 10 * deltaTime;
	}

	void SampleDepthTesting::OnRender()
	{
		for (auto& cube : cubes)
		{
			cube->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
		}
	}

	void SampleDepthTesting::OnImguiRender()
	{
		UIManager::GetInstance()->ShowTransformUI("first cube", cubes[0]->GetTransform());
		UIManager::GetInstance()->ShowCursorUI();
		UIManager::GetInstance()->ShowCameraUI(*camera);

		if(ImGui::Checkbox("Enable Depth Testing", &depthTestEnabled))
		{
			for (auto& cube : cubes)
			{
				cube->GetMaterial().GetShader().SetUniform1i("u_DepthTestEnabled", depthTestEnabled ? 1 : 0);
			}
		}

		if (ImGui::Checkbox("Use Linearized Depth", &isLinerizedDepth))
		{
			for (auto& cube : cubes)
			{
				cube->GetMaterial().GetShader().SetUniform1i("u_LinearizedDepth", isLinerizedDepth ? 1 : 0);
			}
		}
	}
}