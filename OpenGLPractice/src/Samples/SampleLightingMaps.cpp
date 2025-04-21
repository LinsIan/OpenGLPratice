#include "SampleLightingMaps.h"
#include "Sphere.h"
#include "Cube.h"
#include "UIManager.h"

namespace Sample
{ 
    void SampleLightingMaps::UpdateCubeMaterial()
    {
        cube->GetMaterial().GetShader().Bind();
        cube->GetMaterial().SetLightPos(ligthBall->GetTransform().GetTranslation());
        cube->GetMaterial().SetViewPos(camera->GetPosition());
        cube->GetMaterial().SetNormalMatrix(cube->GetTransform().GetNormalMatrix());
    }

    SampleLightingMaps::SampleLightingMaps()
    {
        camera = std::make_unique<Camera>(CameraType::PERSPECTIVE, 960, 540);

        auto lightMaterial = std::make_shared<Material>("res/shaders/Basic3D.shader");
        lightMaterial->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
        ligthBall = std::make_unique<GameObject>(std::make_shared<Model::Sphere>(0.2f, 20, 20), lightMaterial);
        ligthBall->GetTransform().SetTranslation(0.12f, 1.0f, 0.2f);

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
        cube->GetMaterial().SetLightProperties(lightMaterial->GetColor(), {0.2f, 0.5f, 1.0f});
        UpdateCubeMaterial();
    }

    SampleLightingMaps::~SampleLightingMaps()
    {
    }

    void SampleLightingMaps::OnUpdate(float deltaTime)
    {
        cube->GetTransform().GetRotation().x += 6 * deltaTime;
        cube->GetTransform().GetRotation().y += 10 * deltaTime;
        cube->GetTransform().GetRotation().z += 8 * deltaTime;
    }

    void SampleLightingMaps::OnRender()
    {
        ligthBall->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
        UpdateCubeMaterial();
        cube->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
    }

    void SampleLightingMaps::OnImguiRender()
    {
        UIManager::GetInstance()->ShowTransformUI(ligthBall->GetTransform());
        UIManager::GetInstance()->ShowCursorUI();
        UIManager::GetInstance()->ShowCameraUI(*camera);
    }
}