#include "SampleLightTest.h"
#include "Sphere.h"
#include "Cube.h"
#include "UIManager.h"

namespace Sample
{

    void SampleLightTest::UpdatCubeMaterial()
    {
        cube->GetMaterial().GetShader().Bind();
        auto lightColor = ligthBall->GetMaterial().GetColor();
        cube->GetMaterial().GetShader().SetUniform3f("u_LightColor", lightColor.r, lightColor.g, lightColor.b);
        auto lightPos = ligthBall->GetTransform().GetTranslation();
        cube->GetMaterial().GetShader().SetUniform3f("u_LightPos", lightPos.x, lightPos.y, lightPos.z);
        auto viewPos = camera->GetPosition();
        cube->GetMaterial().GetShader().SetUniform3f("u_ViewPos", viewPos.x, viewPos.y, viewPos.z);
        cube->GetMaterial().GetShader().SetUniformMat3f("u_NormalMatrix", cube->GetTransform().GetNormalMatrix());
    }

    SampleLightTest::SampleLightTest()
    {
        camera = std::make_unique<Camera>(CameraType::PERSPECTIVE, 960, 540);

        auto lightMaterial = std::make_shared<Material>("res/shaders/Basic3D.shader");
        lightMaterial->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

        ligthBall = std::make_unique<GameObject>(std::make_shared<Model::Sphere>(0.2f, 20, 20), lightMaterial);
        ligthBall->GetTransform().SetTranslation(0.1f, 0.7f, 0.0f);
        
        auto cubeMaterial = std::make_shared<Material>("res/shaders/Light.shader");
        cubeMaterial->SetColor(1.0f, 0.5f, 0.31f, 1.0f);
        
        cube = std::make_unique<GameObject>(std::make_shared<Model::Cube>(1.0f, 1.0f, 1.0f), cubeMaterial);
        cube->GetTransform().SetRotation(45, 0, 0);
        cube->GetTransform().SetScale(0.6f, 0.6f, 0.6f);

        UpdatCubeMaterial();
    }

    SampleLightTest::~SampleLightTest()
    {
    }

    void SampleLightTest::OnUpdate(float deltaTime)
    {
    
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
    }

}