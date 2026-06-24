#include "SampleEnvironmentMapping.h"
#include "Cube.h"
#include "UIManager.h"

namespace Sample
{
	SampleEnvironmentMapping::SampleEnvironmentMapping()
	{
		skybox = std::make_unique<Skybox>(std::vector<std::string>{
			"res/textures/skybox/right.jpg",
			"res/textures/skybox/left.jpg",
			"res/textures/skybox/top.jpg",
			"res/textures/skybox/bottom.jpg",
			"res/textures/skybox/front.jpg",
			"res/textures/skybox/back.jpg"
		});

        auto skyboxTexture = skybox->GetMaterial().GetTexture(0);

		auto reflectionMaterial = std::make_shared<Material>("res/shaders/Reflection.shader");
        reflectionMaterial->AddTexture(skyboxTexture, 0,"u_Cubemap");
        reflectionMaterial->BindTextures();
        reflectionCube = std::make_unique<GameObject>(std::make_shared<Mesh::Cube>(1.0f, 1.0f, 1.0f), reflectionMaterial);
		reflectionCube->GetTransform().SetTranslation(-1.5f, 0, -3.0f);

        // auto refractionMaterial = std::make_shared<Material>("res/shaders/Refraction.shader");
        // refractionMaterial->AddTexture(skyboxTexture, 0, "u_Cubemap");
        // refractionMaterial->BindTextures();
        // refractionCube = std::make_unique<GameObject>(std::make_shared<Mesh::Cube>(0.8f, 0.8f, 0.8f), refractionMaterial);
        // refractionCube->GetTransform().SetTranslation(1.5f, 0, -3.0f);

		camera = std::make_unique<Camera>(CameraType::PERSPECTIVE, 960.0f, 540.0f);
	}

	SampleEnvironmentMapping::~SampleEnvironmentMapping()
	{
	}

	void SampleEnvironmentMapping::OnUpdate(float deltaTime)
	{
		reflectionCube->GetTransform().GetRotation().y += 1 * deltaTime;
		// refractionCube->GetTransform().GetRotation().x += 1 * deltaTime;
	}

	void SampleEnvironmentMapping::OnRender()
	{
		reflectionCube->GetMaterial().SetViewPos(camera->GetPosition());
		reflectionCube->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
		// refractionCube->GetMaterial().SetViewPos(camera->GetPosition());
		// refractionCube->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
		skybox->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
	}

	void SampleEnvironmentMapping::OnImguiRender()
	{
		UIManager::GetInstance()->ShowCursorUI();
		UIManager::GetInstance()->ShowCameraUI(*camera);
    }
}