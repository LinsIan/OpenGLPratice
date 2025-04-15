#include "SampleLightTest.h"
#include "Sphere.h"
#include "Cube.h"
#include "glfw/glfw3.h"

namespace Sample
{
    SampleLightTest::SampleLightTest()
    {

        auto lightMaterial = std::make_shared<Material>("res/shaders/Basic3D.shader");
        lightMaterial->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

        ligthBall = std::make_unique<GameObject>(std::make_shared<Model::Sphere>(0.2f, 20, 20), lightMaterial);
        ligthBall->GetTransform().SetTranslation(1.5f, 1.2f, -2.0f);
        
        auto cubeMaterial = std::make_shared<Material>("res/shaders/Light.shader");
        cubeMaterial->SetColor(1.0f, 0.5f, 0.31f, 1.0f);
        auto lightColor = lightMaterial->GetColor();
        cubeMaterial->GetShader().SetUniform4f("u_LightColor", lightColor.r, lightColor.g, lightColor.b, lightColor.a);

        cube = std::make_unique<GameObject>(std::make_shared<Model::Cube>(1.0f, 1.0f, 1.0f), cubeMaterial);
        cube->GetTransform().SetRotation(45, 45, 0);
        cube->GetTransform().SetScale(0.5f, 0.5f, 0.5f);

        camera = std::make_unique<Camera>(CameraType::PERSPECTIVE, 960, 540);
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
        cube->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
    }

    void SampleLightTest::OnImguiRender()
    {
        /*if (ImGui::IsKeyPressed(ImGuiKey_F))
        {
            isShowCursor = !isShowCursor;

            if (isShowCursor)
            {
                glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
            else
            {
                glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                lastMousePos = ImGui::GetMousePos();
            }
        }

        if (isShowCursor) return;

        if (ImGui::IsKeyDown(ImGuiKey_W))
        {
            camera->MoveForward();
        }
        if (ImGui::IsKeyDown(ImGuiKey_S))
        {
            camera->MoveBackward();
        }
        if (ImGui::IsKeyDown(ImGuiKey_A))
        {
            camera->MoveLeft();
        }
        if (ImGui::IsKeyDown(ImGuiKey_D))
        {
            camera->MoveRight();
        }

        ImVec2 currentPos = ImGui::GetMousePos();

        if (currentPos.x != lastMousePos.x || currentPos.y != lastMousePos.y)
        {
            float xOffset = currentPos.x - lastMousePos.x;
            float yOffset = lastMousePos.y - currentPos.y;

            camera->Rotate(xOffset, yOffset);
            lastMousePos = currentPos;
        }

        float wheel = ImGui::GetIO().MouseWheel;

        if (wheel != 0.0f)
        {
            camera->SetFov(wheel);
        }*/

    }

}