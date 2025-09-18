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
        pointLight = std::make_unique<Light<PointLightProperties>>(LightType::POINT, pointLightProperties);
            
        CreateCube(dirCube, LightType::DIRECTIONAL);
        CreateCube(pointCube, LightType::POINT);
        currentLightType = LightType::POINT;
    }

    SampleLightCaster::~SampleLightCaster()
    {
    }

    void SampleLightCaster::OnUpdate(float deltaTime)
    {
        dirCube->GetTransform().GetRotation().x += 6 * deltaTime;
        dirCube->GetTransform().GetRotation().y += 10 * deltaTime;
        dirCube->GetTransform().GetRotation().z += 8 * deltaTime;

        pointCube->GetTransform().GetRotation().x += 6 * deltaTime;
        pointCube->GetTransform().GetRotation().y += 10 * deltaTime;
        pointCube->GetTransform().GetRotation().z += 8 * deltaTime;
    }

    void SampleLightCaster::OnRender()
    {
        switch (currentLightType)
        {
        case LightType::DIRECTIONAL:
            dirCube->GetMaterial().UpdateDirLightUniforms(dirLight->GetLightProperties(), camera->GetPosition(), dirCube->GetTransform().GetNormalMatrix());
            dirCube->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
            break;
        case LightType::POINT:
            pointCube->GetMaterial().UpdatePointLightUniforms(pointLight->GetLightProperties(), camera->GetPosition(), pointCube->GetTransform().GetNormalMatrix());
            pointCube->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
            break;
        case LightType::SPOT:
            break;
        default:
            break;
        }

        pointLight->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
    }

    void SampleLightCaster::OnImguiRender()
    {

        if (ImGui::Begin("Light Type"))
        {
            if (ImGui::Combo("Light Type", (int*)&currentLightType, lightTypes, IM_ARRAYSIZE(lightTypes)))
            {
                std::cout << "Current Light Type: " << lightTypes[(int)currentLightType] << std::endl;
            }
        }
        
        ImGui::End();
    }


    void SampleLightCaster::CreateCube(std::unique_ptr<GameObject> &cube, LightType type)
    {
        std::shared_ptr<Material> cubeMaterial;

        switch(type)
        {
            case LightType::DIRECTIONAL:
                cubeMaterial = std::make_shared<Material>("res/shaders/LightCaster/DirLight.shader");
                break;
            case LightType::POINT:
                cubeMaterial = std::make_shared<Material>("res/shaders/LightCaster/PointLight.shader");
                break;
        }

        cubeMaterial->AddTexture("res/textures/container2.png", 0, "material.diffuse");
        cubeMaterial->AddTexture("res/textures/container2_specular.png", 1, "material.specular");
        cubeMaterial->BindTextures();
        cubeMaterial->SetMaterialShininess(64.0f);
        cube = std::make_unique<GameObject>(std::make_shared<Model::Cube>(1.0f, 1.0f, 1.0f), cubeMaterial);
        cube->GetTransform().SetScale(0.6f, 0.6f, 0.6f);
    }
}
