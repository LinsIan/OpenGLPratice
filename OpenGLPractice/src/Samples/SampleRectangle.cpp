#include "SampleRectangle.h"
#include "VertexBufferLayout.h"

namespace Sample
{
    SampleRectangle::SampleRectangle()
    {
        float position[] = 
        {
            -0.5f, -0.5f,
             0.5f, -0.5f,
             0.5f,  0.5f,
            -0.5f,  0.5f,
        };

        unsigned int indices[] =
        {
            0, 1, 2,
            2, 3, 0
        };

        vertexArray = std::make_unique<VertexArray>();
        vertexBuffer = std::make_unique<VertexBuffer>(position, 8 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        vertexArray->AddBuffer(*vertexBuffer, layout);

        indexBuffer = std::make_unique<IndexBuffer>(indices, 6);

        shader = std::make_unique<Shader>("res/shaders/Basic.shader");
        shader->Bind();
        shader->SetUniform4f("u_Color", r, 0.5f, 0.8f, 1.0f);

        renderer = std::make_unique<Renderer>();
    }
    
    SampleRectangle::~SampleRectangle()
    {
    }
    
    void SampleRectangle::OnUpdate(float deltaTime)
    {
        if (r >= 1) increment = -deltaTime;
        else if (r <= 0) increment = deltaTime;

        r += increment;
    }

    void SampleRectangle::OnRender()
	{
		shader->SetUniform4f("u_Color", r, 0.5f, 0.8f, 1.0f);
        renderer->Draw(*vertexArray, *indexBuffer, *shader);
	}
}