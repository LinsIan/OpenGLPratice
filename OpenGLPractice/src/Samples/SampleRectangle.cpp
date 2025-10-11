#include "SampleRectangle.h"
#include "Rectangle.h"

namespace Sample
{
    SampleRectangle::SampleRectangle()
    {
        auto rect = std::make_shared<Mesh::Rectangle>(1.0f, 1.0f, 1.0f, 1.0f);
        rectangle = std::make_unique<GameObject>(rect, "res/shaders/Basic2D.shader");
        
        rectangle->GetMaterial().GetShader().SetUniform4f("u_Color", r, 0.5f, 0.8f, 1.0f);
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
        rectangle->GetMaterial().GetShader().SetUniform4f("u_Color", r, 0.5f, 0.8f, 1.0f);
		rectangle->OnRender();
	}
}