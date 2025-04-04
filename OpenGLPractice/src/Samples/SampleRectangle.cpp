#include "SampleRectangle.h"

namespace Sample
{
    SampleRectangle::SampleRectangle()
    {
        rectangle = std::make_unique<Model::Rectangle>(1.0f, 1.0f, 1.0f, 1.0f);
        
        material = std::make_unique<Material>("res/shaders/Basic.shader");
        material->GetShader().SetUniform4f("u_Color", r, 0.5f, 0.8f, 1.0f);

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
		material->GetShader().SetUniform4f("u_Color", r, 0.5f, 0.8f, 1.0f);
        renderer->Draw(rectangle->GetVertexArray(), rectangle->GetIndexBuffer(), material->GetShader());
	}
}