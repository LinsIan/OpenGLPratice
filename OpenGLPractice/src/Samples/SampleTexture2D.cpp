#include "SampleTexture2D.h"
#include "imgui/imgui.h"


namespace Sample
{
    SampleTexture2D::SampleTexture2D()
    {
        float position[] =
        {
            -50.0f, -50.0f, 0.0f, 0.0f, // 0
             50.0f, -50.0f, 1.0f, 0.0f, // 1
             50.0f,  50.0f, 1.0f, 1.0f, // 2
            -50.0f,  50.0f, 0.0f, 1.0f  // 3
        };

        unsigned int indeces[] =
        {
            0, 1, 2,
            2, 3, 0
        };

        vertexArray = std::make_unique<VertexArray>();
        vertexBuffer = std::make_unique<VertexBuffer>(position, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2); // position
        layout.Push<float>(2); // texture coordinate
        vertexArray->AddBuffer(*vertexBuffer, layout);

        indexBuffer = std::make_unique<IndexBuffer>(indeces, 6); // index buffer binding must be done after vertex buffer binding

        translation = glm::vec3(200, 200, 0);
        scale = glm::vec3(1.0f, 1.0f, 1.0f);
        radians = 0.0f;
		proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f); // 正交投影
        view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)); // move camera
        model = glm::mat4(1.0f);

        shader = std::make_unique<Shader>("res/shaders/Texture.shader");
        shader->Bind();
        shader->SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

        texture = std::make_unique<Texture>("res/textures/ChernoLogo.png");
        unsigned int slot = 0;
        texture->Bind(slot);
        shader->SetUniform1i("u_Texture", slot);

        vertexArray->Unbind();
        vertexBuffer->Unbind();
        indexBuffer->Unbind();
        shader->Unbind();

        renderer = std::make_unique<Renderer>();
    }
    
    SampleTexture2D::~SampleTexture2D()
    {
        
    }
    
    void SampleTexture2D::OnUpdate(float deltaTime)
    {
        if (isRotation)
        {
            radians += deltaTime * 20;
        }
    }
    
    void SampleTexture2D::OnRender()
    {
        shader->Bind();

        model = glm::translate(glm::mat4(1.0f), translation); // translate model

        if (isRotation)
        {
            model = glm::rotate(model, glm::radians(-radians), glm::vec3(0, 0, 1)); // rotate model
        }

        model = glm::scale(model, scale); // scale model

        glm::mat4 mvp = proj * view * model;
        shader->SetUniformMat4f("u_MVP", mvp);

        renderer->Draw(*vertexArray, *indexBuffer, *shader);
    }
    
    void SampleTexture2D::OnImguiRender()
    {
        ImGui::SliderFloat3("Model translation A:", &translation.x, 0.0f, 960.0f);
        ImGui::Checkbox("Model rotation", &isRotation);
        ImGui::SliderFloat3("Model scale:", &scale.x, 0.1f, 5.0f);
        // ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    }

}