#include "SampleLightTest.h"
#include "Sphere.h"
#include "Cube.h"
#include "UIManager.h"

#include <iostream>

namespace Sample
{

    void SampleLightTest::UpdatCubeMaterial()
    {
        cube->GetMaterial().GetShader().Bind();
        cube->GetMaterial().SetLightColor(ligthBall->GetMaterial().GetColor(), lightStrength);
        cube->GetMaterial().SetLightPos(ligthBall->GetTransform().GetTranslation());
        cube->GetMaterial().SetViewPos(camera->GetPosition());
        cube->GetMaterial().SetNormalMatrix(cube->GetTransform().GetNormalMatrix());
    }

    SampleLightTest::SampleLightTest()
    {
        camera = std::make_unique<Camera>(CameraType::PERSPECTIVE, 960, 540);
        lightStrength = glm::vec3(1.0f, 1.0f, 1.0f);

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
        cube->GetMaterial().SetMaterialProperties(currentMaterial);
        UpdatCubeMaterial();
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