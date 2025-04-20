#include "SampleLightTest.h"
#include "Sphere.h"
#include "Cube.h"
#include "UIManager.h"

#include <iostream>

namespace Sample
{

    void SampleLightTest::UpdatCubeMaterial()
    {
		lightStrength = glm::vec3(1.0f, 1.0f, 1.0f);
        cube->GetMaterial().GetShader().Bind();
        auto lightColor = ligthBall->GetMaterial().GetColor();
        cube->GetMaterial().GetShader().SetUniform3f("light.ambient", lightColor.r * lightStrength.x, lightColor.g * lightStrength.x, lightColor.b * lightStrength.x);
        cube->GetMaterial().GetShader().SetUniform3f("light.diffuse", lightColor.r * lightStrength.y, lightColor.g * lightStrength.y, lightColor.b * lightStrength.y);
        cube->GetMaterial().GetShader().SetUniform3f("light.specular", lightColor.r * lightStrength.z, lightColor.g * lightStrength.z, lightColor.b * lightStrength.z);
        auto lightPos = ligthBall->GetTransform().GetTranslation();
        cube->GetMaterial().GetShader().SetUniform3f("light.position", lightPos.x, lightPos.y, lightPos.z);
        auto viewPos = camera->GetPosition();
        cube->GetMaterial().GetShader().SetUniform3f("u_ViewPos", viewPos.x, viewPos.y, viewPos.z);
        cube->GetMaterial().GetShader().SetUniformMat3f("u_NormalMatrix", cube->GetTransform().GetNormalMatrix());
    }

	void SampleLightTest::OnCurrentMaterialChange()
	{
		cube->GetMaterial().GetShader().SetUniform3f("material.ambient", currentMaterial.ambient.x, currentMaterial.ambient.y, currentMaterial.ambient.z);
		cube->GetMaterial().GetShader().SetUniform3f("material.diffuse", currentMaterial.diffuse.x, currentMaterial.diffuse.y, currentMaterial.diffuse.z);
		cube->GetMaterial().GetShader().SetUniform3f("material.specular", currentMaterial.specular.x, currentMaterial.specular.y, currentMaterial.specular.z);
		cube->GetMaterial().GetShader().SetUniform1f("material.shininess", currentMaterial.shininess);

		currentMaterial = database.GetMaterialProperties(MaterialType::Emerald);

		UpdatCubeMaterial();
	}

    SampleLightTest::SampleLightTest()
    {
        camera = std::make_unique<Camera>(CameraType::PERSPECTIVE, 960, 540);

        auto lightMaterial = std::make_shared<Material>("res/shaders/Basic3D.shader");
        lightMaterial->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

        ligthBall = std::make_unique<GameObject>(std::make_shared<Model::Sphere>(0.2f, 20, 20), lightMaterial);
        ligthBall->GetTransform().SetTranslation(0.12f, 1.0f, 0.2f);
        
        auto cubeMaterial = std::make_shared<Material>("res/shaders/Light.shader");
        cubeMaterial->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
        
        cube = std::make_unique<GameObject>(std::make_shared<Model::Cube>(1.0f, 1.0f, 1.0f), cubeMaterial);
        cube->GetTransform().SetRotation(45, 0, 0);
        cube->GetTransform().SetScale(0.6f, 0.6f, 0.6f);

        currentMaterial = database.GetMaterialProperties(MaterialType::Emerald);
        UpdatCubeMaterial();
        OnCurrentMaterialChange();
    }

    SampleLightTest::~SampleLightTest()
    {
    }

    void SampleLightTest::OnUpdate(float deltaTime)
    {
        cube->GetTransform().GetRotation().y += 10 * deltaTime;
        cube->GetTransform().GetRotation().z += 8 * deltaTime;
    }
    
    void SampleLightTest::OnRender()
    {
        ligthBall->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
        UpdatCubeMaterial();
        cube->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
    }

    void SampleLightTest::OnImguiRender()
    {
        UIManager::GetInstance()->ShowTransformUI(ligthBall->GetTransform());
        UIManager::GetInstance()->ShowCursorUI();
        UIManager::GetInstance()->ShowCameraUI(*camera);

        int buttonCount = 0;

		for (auto& materialProperties : database.GetAllMaterialProperties())
		{
			if (ImGui::Button(MaterialTypeToString(materialProperties.first).c_str()))
            {
				currentMaterial = materialProperties.second;
                OnCurrentMaterialChange();
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