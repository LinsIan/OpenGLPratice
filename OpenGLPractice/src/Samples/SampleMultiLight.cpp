#include "SampleMultiLight.h"
#include "Cube.h"
#include "UIManager.h"

namespace Sample
{
    SampleMultiLight::SampleMultiLight()
    {
        camera = std::make_unique<Camera>(CameraType::PERSPECTIVE, 960, 540);
        camera->GetPosition().z = 6;

        DirLightProperties lightProperties;
        lightProperties.direction = { -0.2f, -1.0f, -0.3f };
        lightProperties.ambient = { 0.05f, 0.05f, 0.05f };
        lightProperties.diffuse = { 0.4f, 0.4f, 0.4f };
        lightProperties.specular = { 0.5f, 0.5f, 0.5f };
        dirLight = std::make_unique<Light<DirLightProperties>>(LightType::DIRECTIONAL, lightProperties);

  
        PointLightProperties bluePointLightProperties;
        bluePointLightProperties.position = { 2.0f, 0.5f, 1.5f };
        bluePointLightProperties.ambient = { 0.0f, 0.0f, 0.05f };
        bluePointLightProperties.diffuse = { 0.0f, 0.0f, 0.8f };
        bluePointLightProperties.specular = { 0.0f, 0.0f, 1.0f };
        bluePointLightProperties.constant = 1.0f;
        bluePointLightProperties.linear = 0.09f;
        bluePointLightProperties.quadratic = 0.032f;
		pointLights.emplace_back(std::make_unique<Light<PointLightProperties>>(LightType::POINT, bluePointLightProperties));

        PointLightProperties greenPointLightProperties;
        greenPointLightProperties.position = { -2.0f, 0.5f, 1.5f };
        greenPointLightProperties.ambient = { 0.0f, 0.05f, 0.0f };
        greenPointLightProperties.diffuse = { 0.0f, 0.8f, 0.0f };
        greenPointLightProperties.specular = { 0.0f, 1.0f, 0.0f };
        greenPointLightProperties.constant = 1.0f;
        greenPointLightProperties.linear = 0.09f;
        greenPointLightProperties.quadratic = 0.032f;
        pointLights.emplace_back(std::make_unique<Light<PointLightProperties>>(LightType::POINT, greenPointLightProperties));

        SpotLightProperties spotLightProperties;
        spotLightProperties.position = camera->GetPosition();
		spotLightProperties.position.z -= 3.0f;
        spotLightProperties.direction = camera->GetForward();
        spotLightProperties.cutOff = glm::cos(glm::radians(6.25f));
        spotLightProperties.outerCutOff = glm::cos(glm::radians(8.75f));
        spotLightProperties.ambient = glm::vec3(0.0f, 0.0f, 0.0f);
        spotLightProperties.diffuse = glm::vec3(0.8f, 0.0f, 0.0f);
        spotLightProperties.specular = glm::vec3(1.0f, 0.0f, 0.0f);
        spotLightProperties.constant = 1.0f;
        spotLightProperties.linear = 0.09f;
        spotLightProperties.quadratic = 0.032f;
        spotLight = std::make_unique<Light<SpotLightProperties>>(LightType::SPOT, spotLightProperties);

        for (int i = 0; i < 2; ++i)
        {
            auto cubeMaterial = std::make_shared<Material>("res/shaders/MultiLights.shader");
            cubeMaterial->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
            cubeMaterial->AddTexture("res/textures/container2.png", 0, "material.diffuse");
            cubeMaterial->AddTexture("res/textures/container2_specular.png", 1, "material.specular");
            cubeMaterial->BindTextures();

            cubes.emplace_back(std::make_unique<GameObject>(std::make_shared<Mesh::Cube>(1.0f, 1.0f, 1.0f), cubeMaterial));
            cubes[i]->GetTransform().SetRotation(45, 0, 0);
            cubes[i]->GetTransform().SetScale(0.8f, 0.8f, 0.8f);
            cubes[i]->GetMaterial().GetShader().Bind();
            cubes[i]->GetMaterial().SetMaterialShininess(64.0f);
            cubes[i]->GetMaterial().SetPointLightsNum(pointLights.size());
		}
        
		cubes[0]->GetTransform().SetTranslation(-.5f, 0.0f, 0.0f);
        cubes[1]->GetTransform().SetTranslation(0.5f, 0.0f, 0.0f);
    }
    
    SampleMultiLight::~SampleMultiLight()
    {
    }

    void SampleMultiLight::OnUpdate(float deltaTime)
    {
        for (auto& cube : cubes)
        {
            cube->GetTransform().GetRotation().x += 6 * deltaTime;
            cube->GetTransform().GetRotation().y += 10 * deltaTime;
            cube->GetTransform().GetRotation().z += 8 * deltaTime;
		}
        
        for (auto& pointLight : pointLights)
        {
            pointLight->OnUpdate(deltaTime);
        }
    }

    void SampleMultiLight::OnRender()
    {
        for (auto& cube : cubes)
        {
            cube->GetMaterial().UpdateDirLightUniforms(dirLight->GetLightProperties(), camera->GetPosition(), cube->GetTransform().GetNormalMatrix());

            for (size_t i = 0; i < pointLights.size(); ++i)
            {
                cube->GetMaterial().UpdatePointLightUniforms(i, pointLights[i]->GetLightProperties());
            }

            cube->GetMaterial().UpdateSpotLightUniforms(spotLight->GetLightProperties(), camera->GetPosition(), cube->GetTransform().GetNormalMatrix());

            cube->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
		}

        for (auto& pointLight : pointLights)
        {
            pointLight->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
        }
    }
    
    void SampleMultiLight::OnImguiRender()
    {
        for (size_t i = 0; i < pointLights.size(); ++i)
        {
            UIManager::GetInstance()->ShowTransformUI("Point Light " + std::to_string(i + 1), pointLights[i]->GetTransform(), 2.5f);
        }
    }
}