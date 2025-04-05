#include "SampleTexture2D.h"
#include "imgui/imgui.h"


namespace Sample
{
    SampleTexture2D::SampleTexture2D()
    {
        rectangle = std::make_unique<Model::Rectangle>(100, 100, 1.0f, 1.0f);
        rectangle->SetTranslation(200, 200, 0);

		proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f); // 正交投影
        view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)); // move camera

        shader = std::make_unique<Shader>("res/shaders/Texture.shader");
        shader->Bind();
        shader->SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

        texture = std::make_unique<Texture>("res/textures/ChernoLogo.png");
        unsigned int slot = 0;
        texture->Bind(slot);
        shader->SetUniform1i("u_Texture", slot);

        shader->Unbind();

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
        shader->Bind();
        glm::mat4 mvp = proj * view * rectangle->GetModelMatrix();
        shader->SetUniformMat4f("u_MVP", mvp);

        renderer->Draw(rectangle->GetVertexArray(), rectangle->GetIndexBuffer(), *shader);
    }
    
    void SampleTexture2D::OnImguiRender()
    {
        ImGui::SliderFloat3("Model translation A:", &rectangle->GetTranslation().x, 0.0f, 960.0f);
        ImGui::SliderFloat3("Model rotation:", &rectangle->GetRotation().x, 0.0f, 360.0f);
        ImGui::SliderFloat3("Model scale:", &rectangle->GetScale().x, 0.1f, 5.0f);
        // ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    }

}