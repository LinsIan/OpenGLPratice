#include "SampleTexture3D.h"
#include "Cube.h"
#include "UIManager.h"

namespace Sample
{
	SampleTexture3D::SampleTexture3D()
	{
        auto material = std::make_shared<Material>("res/shaders/TextureMix.shader");
        material->AddTexture("res/textures/awesomeface.png", 0, "u_TextureA");
        material->AddTexture("res/textures/container.jpg", 1, "u_TextureB");
        material->BindTextures();
        material->GetShader().SetUniform1f("u_Degree", 0.8f);

		auto cube1 = std::make_unique<GameObject>(std::make_shared<Model::Cube>(1.0f, 1.0f, 1.0f), material);
        auto cube2 = std::make_unique<GameObject>(std::make_shared<Model::Cube>(1.2f, 1.2f, 1.2f), material);
        auto cube3 = std::make_unique<GameObject>(std::make_shared<Model::Cube>(0.6f, 0.8f, 1.4f), material);

        cubes.push_back(std::move(cube1));
        cubes.push_back(std::move(cube2));
        cubes.push_back(std::move(cube3));

		cubes[1]->GetTransform().SetTranslation(-1.3f, 0, -0.8f);
		cubes[1]->GetTransform().SetRotation(30, 34, -13);

		cubes[2]->GetTransform().SetTranslation(1.3f, 0, -0.6f);
		cubes[2]->GetTransform().SetRotation(-38, 60, 34);

		camera = std::make_unique<Camera>(CameraType::PERSPECTIVE, 960.0f, 540.0f);
	}

	SampleTexture3D::~SampleTexture3D()
	{
	}
 	
	void SampleTexture3D::OnUpdate(float deltaTime)
	{
		cubes[1]->GetTransform().GetRotation().y += 10 * deltaTime;
		cubes[2]->GetTransform().GetRotation().x += 10 * deltaTime;
	}

	void SampleTexture3D::OnRender()
	{
        for (auto& cube : cubes)
        {
            cube->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
        }
	}

	void SampleTexture3D::OnImguiRender()
	{
		UIManager::GetInstance()->ShowTransformUI("first cube", cubes[0]->GetTransform());
        UIManager::GetInstance()->ShowCursorUI();
        UIManager::GetInstance()->ShowCameraUI(*camera);
	}
}