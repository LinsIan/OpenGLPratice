#include "SampleTexture2D.h"
#include "imgui/imgui.h"

glm::mat4 projection;
namespace Sample
{
    SampleTexture2D::SampleTexture2D()
    {
        rectangle = std::make_unique<Model::Rectangle>(100, 100, 1.0f, 1.0f);
        rectangle->SetTranslation(200, 200, 0);

        camera = std::make_unique<Camera>(CameraType::ORTHOGRAPHIC, 960.0f, 540.0f);

        material = std::make_unique<Material>("res/shaders/Texture.shader");
        material->AddTexture("res/textures/ChernoLogo.png", 0, "u_Texture");
        material->GetShader().SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

        renderer = std::make_unique<Renderer>();
    }
    
    SampleTexture2D::~SampleTexture2D()
    {
        
    }
    
    void SampleTexture2D::OnUpdate(float deltaTime)
    {
    }
    
    void SampleTexture2D::OnRender()
    {
        glm::mat4 mvp = camera->GetProjectionMatrix() * camera->GetViewMatrix() * rectangle->GetModelMatrix();
        material->GetShader().SetUniformMat4f("u_MVP", mvp);

        renderer->Draw(rectangle->GetVertexArray(), rectangle->GetIndexBuffer(), material->GetShader());
    }
    
    void SampleTexture2D::OnImguiRender()
    {
		ImGui::Text("Camera: Orthographic");
        ImGui::SliderFloat3("Model translation A:", &rectangle->GetTranslation().x, -3.0f, 960.0f);
        ImGui::SliderFloat3("Model rotation:", &rectangle->GetRotation().x, 0.0f, 360.0f);
        ImGui::SliderFloat3("Model scale:", &rectangle->GetScale().x, 0.1f, 5.0f);
    }

}