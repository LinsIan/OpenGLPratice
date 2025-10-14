#include "SampleImportModel.h"
#include <filesystem>

namespace Sample
{
    SampleImportModel::SampleImportModel()
    {
        camera = std::make_unique<Camera>(CameraType::PERSPECTIVE, 1280, 720);

        DirLightProperties dirLightProperties;
        dirLightProperties.direction = glm::vec3(-0.2f, -1.0f, -0.3f);
        dirLightProperties.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
        dirLightProperties.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
        dirLightProperties.specular = glm::vec3(1.0f, 1.0f, 1.0f);
        dirLight = std::make_unique<Light<DirLightProperties>>(LightType::DIRECTIONAL, dirLightProperties);

#if defined(__APPLE__)
        string path = std::filesystem::absolute("../res/models/backpack/backpack.obj").string();
        path = std::filesystem::canonical(path).string();
#else
        string path = std::filesystem::absolute("res/models/backpack/backpack.obj").string();
#endif
        std::cout << "Model path: " << path << std::endl;

        backpackModel = std::make_unique<Model>(path);
    }
    
    SampleImportModel::~SampleImportModel()
    {
        
    }
    
    void SampleImportModel::OnUpdate(float deltaTime)
    {
        
    }
    
    void SampleImportModel::OnRender()
    {
        backpackModel->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
    }
    
    void SampleImportModel::OnImguiRender()
    {
        
    }
}