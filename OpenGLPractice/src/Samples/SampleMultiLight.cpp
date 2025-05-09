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
        lightProperties.ambient = { 0.2f, 0.2f, 0.2f };
        lightProperties.diffuse = { 0.5f, 0.5f, 0.5f };
        lightProperties.specular = { 1.0f, 1.0f, 1.0f };

        dirLight = std::make_unique<Light<DirLightProperties>>(LightType::DIRECTIONAL, lightProperties);

        PointLightProperties pointLightProperties;
        pointLightProperties.position = { 1.0f, 1.0f, 1.0f };
        pointLightProperties.ambient = { 0.2f, 0.2f, 0.2f };
        pointLightProperties.diffuse = { 0.5f, 0.5f, 0.5f };
        pointLightProperties.specular = { 1.0f, 1.0f, 1.0f };
        pointLightProperties.constant = 1.0f;
        pointLightProperties.linear = 0.09f;
        pointLightProperties.quadratic = 0.032f;

        pointLight = std::make_unique<Light<PointLightProperties>>(LightType::POINT, pointLightProperties);

        auto cubeMaterial = std::make_shared<Material>("res/shaders/MultiLights.shader");
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
    
    SampleMultiLight::~SampleMultiLight()
    {
    }

    void SampleMultiLight::OnUpdate(float deltaTime)
    {
        cube->GetTransform().GetRotation().x += 6 * deltaTime;
        cube->GetTransform().GetRotation().y += 10 * deltaTime;
        cube->GetTransform().GetRotation().z += 8 * deltaTime;

        dirLight->OnUpdate(deltaTime);
        pointLight->OnUpdate(deltaTime);
    }

    void SampleMultiLight::OnRender()
    {
        cube->GetMaterial().UpdateDirLightUniforms(dirLight->GetLightProperties(), camera->GetPosition(), cube->GetTransform().GetNormalMatrix());
        cube->GetMaterial().SetPointLightProperties(pointLight->GetLightProperties());
        cube->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());

        pointLight->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
    }
    
    void SampleMultiLight::OnImguiRender()
    {
        
    }
}