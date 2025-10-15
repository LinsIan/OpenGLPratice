#include "SampleImportModel.h"
#include "UIManager.h"
#include <filesystem>

namespace Sample
{
    SampleImportModel::SampleImportModel()
    {
        camera = std::make_unique<Camera>(CameraType::PERSPECTIVE, 1280, 720);

        DirLightProperties dirLightProperties;
        dirLightProperties.direction = { -0.2f, -1.0f, -0.3f };
        dirLightProperties.ambient = { 0.05f, 0.05f, 0.05f };
        dirLightProperties.diffuse = { 0.4f, 0.4f, 0.4f };
        dirLightProperties.specular = { 0.5f, 0.5f, 0.5f };
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

        SpotLightProperties spotLightProperties;
        spotLightProperties.position = camera->GetPosition();
        spotLightProperties.direction = camera->GetForward();
        spotLightProperties.cutOff = glm::cos(glm::radians(3.125f));
        spotLightProperties.outerCutOff = glm::cos(glm::radians(4.375f));
        spotLightProperties.ambient = glm::vec3(0.1f, 0.1f, 0.1f);
        spotLightProperties.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
        spotLightProperties.specular = glm::vec3(1.0f, 1.0f, 1.0f);
        spotLightProperties.constant = 1.0f;
        spotLightProperties.linear = 0.09f;
        spotLightProperties.quadratic = 0.032f;
        spotLight = std::make_unique<Light<SpotLightProperties>>(LightType::SPOT, spotLightProperties);

#if defined(__APPLE__)
        string path = std::filesystem::absolute("../res/models/backpack/backpack.obj").string();
        path = std::filesystem::canonical(path).string();
#else
        string path = std::filesystem::absolute("res/models/backpack/backpack.obj").string();
        std::replace(path.begin(), path.end(), '\\', '/');
#endif
        std::cout << "Model path: " << path << std::endl;

        backpackModel = std::make_unique<Model>(path);
        backpackModel->GetTransform().SetScale(0.3f, 0.3f, 0.3f);
        for (auto& [index, material] : backpackModel->GetMaterialMap())
        {
            material->BindShader();
            material->SetPointLightsNum(1);
        }
    }
    
    SampleImportModel::~SampleImportModel()
    {
        
    }
    
    void SampleImportModel::OnUpdate(float deltaTime)
    {
        pointLight->OnUpdate(deltaTime);
    }
    
    void SampleImportModel::OnRender()
    {
        for (auto& [index, material] : backpackModel->GetMaterialMap())
        {
            material->BindShader();
            material->UpdateDirLightUniforms(dirLight->GetLightProperties(), camera->GetPosition(), backpackModel->GetTransform().GetNormalMatrix());
            material->UpdatePointLightUniforms(0, pointLight->GetLightProperties());
            material->UpdateSpotLightUniforms(spotLight->GetLightProperties(), camera->GetPosition(), backpackModel->GetTransform().GetNormalMatrix());
        }

        backpackModel->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
        pointLight->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
    }
    
    void SampleImportModel::OnImguiRender()
    {
        UIManager::GetInstance()->ShowTransformUI("Model Transform", backpackModel->GetTransform());
        UIManager::GetInstance()->ShowTransformUI("Point Light Transform", pointLight->GetTransform(), 5.0f);
    }
}