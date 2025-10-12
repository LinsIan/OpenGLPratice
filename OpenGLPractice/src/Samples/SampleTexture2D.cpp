#include "SampleTexture2D.h"
#include "imgui/imgui.h"
#include "Rectangle.h"

glm::mat4 projection;
namespace Sample
{
    SampleTexture2D::SampleTexture2D()
    {
        auto rect = std::make_shared<Mesh::Rectangle>(100, 100, 1.0f, 1.0f);

        auto material = std::make_shared<Material>("res/shaders/Texture.shader");
        material->AddTexture("res/textures/ChernoLogo.png", 0, "u_Texture");
        material->BindTextures();
        rectangle = std::make_unique<GameObject>(rect, material);

        rectangle->GetTransform().SetTranslation(200, 200, 0);
        camera = std::make_unique<Camera>(CameraType::ORTHOGRAPHIC, 960.0f, 540.0f);
    }
    
    SampleTexture2D::~SampleTexture2D()
    {
    }
    
    void SampleTexture2D::OnUpdate(float deltaTime)
    {
    }
    
    void SampleTexture2D::OnRender()
    {
        rectangle->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
    }
    
    void SampleTexture2D::OnImguiRender()
    {
		ImGui::Text("Camera: Orthographic");
        ImGui::SliderFloat3("Model translation A:", &rectangle->GetTransform().GetTranslation().x, -3.0f, 960.0f);
        ImGui::SliderFloat3("Model rotation:", &rectangle->GetTransform().GetRotation().x, 0.0f, 360.0f);
        ImGui::SliderFloat3("Model scale:", &rectangle->GetTransform().GetScale().x, 0.1f, 5.0f);
    }

}