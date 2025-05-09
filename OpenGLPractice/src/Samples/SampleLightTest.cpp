#include "SampleLightTest.h"
#include "Sphere.h"
#include "Cube.h"
#include "UIManager.h"

#include <iostream>

namespace Sample
{

    SampleLightTest::SampleLightTest()
    {
        camera = std::make_unique<Camera>(CameraType::PERSPECTIVE, 960, 540);
        lightStrength = glm::vec3(1.0f, 1.0f, 1.0f);

		BaseLightProperties lightProperties;
		lightProperties.position = glm::vec3(0.12f, 1.0f, 0.2f);
		lightProperties.ambient = glm::vec3(1.0f, 1.0f, 1.0f);
		lightProperties.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
		lightProperties.specular = glm::vec3(1.0f, 1.0f, 1.0f);
		light = std::make_unique<Light<BaseLightProperties>>(LightType::POINT, lightProperties);

        auto cubeMaterial = std::make_shared<Material>("res/shaders/Light.shader");
        cubeMaterial->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
        
        cube = std::make_unique<GameObject>(std::make_shared<Model::Cube>(1.0f, 1.0f, 1.0f), cubeMaterial);
        cube->GetTransform().SetRotation(45, 0, 0);
        cube->GetTransform().SetScale(0.6f, 0.6f, 0.6f);

        currentMaterial = database.GetMaterialProperties(MaterialType::Emerald);
        cube->GetMaterial().SetMaterialProperties(currentMaterial);
    }

    SampleLightTest::~SampleLightTest()
    {
    }

    void SampleLightTest::OnUpdate(float deltaTime)
    {
        cube->GetTransform().GetRotation().y += 10 * deltaTime;
        cube->GetTransform().GetRotation().z += 8 * deltaTime;

		light->OnUpdate(deltaTime);
    }
    
    void SampleLightTest::OnRender()
    {
        light->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
		cube->GetMaterial().UpdateBasicLightUniforms(light->GetLightProperties(), camera->GetPosition(), cube->GetTransform().GetNormalMatrix());
        cube->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
    }

    void SampleLightTest::OnImguiRender()
    {
        UIManager::GetInstance()->ShowTransformUI(light->GetTransform());
        UIManager::GetInstance()->ShowCursorUI();
        UIManager::GetInstance()->ShowCameraUI(*camera);

        int buttonCount = 0;

		for (auto& materialProperties : database.GetAllMaterialProperties())
		{
			if (ImGui::Button(MaterialTypeToString(materialProperties.first).c_str()))
            {
				currentMaterial = materialProperties.second;
                cube->GetMaterial().SetMaterialProperties(currentMaterial);
            }

			buttonCount++;
			ImGui::SameLine();

			if (buttonCount % 4 == 0)
			{
				ImGui::NewLine();
			}
        }
    }

}