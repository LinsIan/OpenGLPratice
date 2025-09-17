#include "SampleLightCaster.h"
#include "Cube.h"
#include "UIManager.h"

namespace Sample
{
    SampleLightCaster::SampleLightCaster()
    {
        camera = std::make_unique<Camera>(CameraType::PERSPECTIVE, 960, 540);

        DirLightProperties dirLightProperties;
        dirLightProperties.direction = glm::vec3(-0.2f, -1.0f, -0.3f);
        dirLightProperties.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
        dirLightProperties.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
        dirLightProperties.specular = glm::vec3(1.0f, 1.0f, 1.0f);

        dirLight = std::make_unique<Light<DirLightProperties>>(LightType::DIRECTIONAL, dirLightProperties);

        PointLightProperties pointLightProperties;
        pointLightProperties.position = glm::vec3(0.12f, 1.0f, 0.2f);
        pointLightProperties.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
        pointLightProperties.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
        pointLightProperties.specular = glm::vec3(1.0f, 1.0f, 1.0f);
        pointLightProperties.constant = 1.0f;
        pointLightProperties.linear = 0.09f;
        pointLightProperties.quadratic = 0.032f;
            

        CreateCube(currentLightType);
    }

    SampleLightCaster::~SampleLightCaster()
    {
    }

    void SampleLightCaster::OnUpdate(float deltaTime)
    {
        cube->GetTransform().GetRotation().x += 6 * deltaTime;
        cube->GetTransform().GetRotation().y += 10 * deltaTime;
        cube->GetTransform().GetRotation().z += 8 * deltaTime;
    }

    void SampleLightCaster::OnRender()
    {
        cube->GetMaterial().UpdateDirLightUniforms(dirLight->GetLightProperties(), camera->GetPosition(), cube->GetTransform().GetNormalMatrix());

        cube->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
        dirLight->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
        pointLight->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
    }

    void SampleLightCaster::OnImguiRender()
    {

        if (ImGui::Begin("Light Type"))
        {
            if (ImGui::Combo("Light Type", (int*)&currentLightType, lightTypes, IM_ARRAYSIZE(lightTypes)))
            {
                
            }
        }
        
        ImGui::End();
    }


    void SampleLightCaster::CreateCube(LightType type)
    {
        if (type == LightType::DIRECTIONAL)
        {
            auto cubeMaterial = std::make_shared<Material>("res/shaders/LightCaster/DirLight.shader");
            cubeMaterial->AddTexture("res/textures/container2.png", 0, "material.diffuse");
            cubeMaterial->AddTexture("res/textures/container2_specular.png", 1, "material.specular");
            cubeMaterial->BindTextures();
            cubeMaterial->SetMaterialShininess(64.0f);
            cube = std::make_unique<GameObject>(std::make_shared<Model::Cube>(1.0f, 1.0f, 1.0f), cubeMaterial);
            cube->GetTransform().SetScale(0.6f, 0.6f, 0.6f);
        }
    }
}
