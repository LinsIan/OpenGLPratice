#include "SampleLightingMaps.h"
#include "Sphere.h"
#include "Cube.h"
#include "UIManager.h"

namespace Sample
{ 
    SampleLightingMaps::SampleLightingMaps()
    {
        camera = std::make_unique<Camera>(CameraType::PERSPECTIVE, 960, 540);

		BaseLightProperties lightProperties;
		lightProperties.position = glm::vec3(0.12f, 1.0f, 0.2f);
		lightProperties.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
		lightProperties.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
		lightProperties.specular = glm::vec3(1.0f, 1.0f, 1.0f);
		light = std::make_unique<Light<BaseLightProperties>>(LightType::POINT, lightProperties);

        auto cubeMaterial = std::make_shared<Material>("res/shaders/LightMaps.shader");
        cubeMaterial->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
        cubeMaterial->AddTexture("res/textures/container2.png", 0, "material.diffuse");
        cubeMaterial->AddTexture("res/textures/container2_specular.png", 1, "material.specular");
        cubeMaterial->BindTextures();

        cube = std::make_unique<GameObject>(std::make_shared<Model::Cube>(1.0f, 1.0f, 1.0f), cubeMaterial);
        cube->GetTransform().SetRotation(45, 0, 0);
        cube->GetTransform().SetScale(0.6f, 0.6f, 0.6f);

        cube->GetMaterial().GetShader().Bind();
        cube->GetMaterial().SetMaterialShininess(64.0f);
    }

    SampleLightingMaps::~SampleLightingMaps()
    {
    }

    void SampleLightingMaps::OnUpdate(float deltaTime)
    {
        cube->GetTransform().GetRotation().x += 6 * deltaTime;
        cube->GetTransform().GetRotation().y += 10 * deltaTime;
        cube->GetTransform().GetRotation().z += 8 * deltaTime;

		light->OnUpdate(deltaTime);
    }

    void SampleLightingMaps::OnRender()
    {
        light->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
        cube->GetMaterial().UpdateBasicLightUniforms(light->GetLightProperties(), camera->GetPosition(), cube->GetTransform().GetNormalMatrix());
        cube->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
    }

    void SampleLightingMaps::OnImguiRender()
    {
        UIManager::GetInstance()->ShowTransformUI("light", light->GetTransform());
        UIManager::GetInstance()->ShowCursorUI();
        UIManager::GetInstance()->ShowCameraUI(*camera);
    }
}