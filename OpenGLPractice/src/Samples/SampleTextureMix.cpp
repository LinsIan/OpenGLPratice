#include "SampleTextureMix.h"

#include "imgui/imgui.h"


namespace Sample
{
	SampleTextureMix::SampleTextureMix()
	{
		mixValue = 0.8f;

		rectangle = std::make_unique<Model::Rectangle>(1.0f, 1.0f, 2.0f, 2.0f);

		filteringMode = GL_LINEAR; // GL_NEAREST
		wrappingMode = GL_REPEAT; // GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER, GL_REPEAT, GL_MIRRORED_REPEAT

		material = std::make_unique<Material>("res/shaders/TextureMix.shader");
		material->AddTexture("res/textures/awesomeface.png", 0, "u_TextureA", filteringMode, wrappingMode);
		material->AddTexture("res/textures/container.jpg", 1, "u_TextureB", filteringMode, wrappingMode);

		auto shader = material->GetShader();
		shader.SetUniform1f("u_Degree", mixValue);
		
		renderer = std::make_unique<Renderer>();
	}

	SampleTextureMix::~SampleTextureMix()
	{
	}

	void SampleTextureMix::OnRender()
	{
		material->GetShader().SetUniform1f("u_Degree", mixValue);
		renderer->Draw(rectangle->GetVertexArray(), rectangle->GetIndexBuffer(), material->GetShader());
	}

	void SampleTextureMix::OnImguiRender()
	{
		ImGui::SliderFloat("mix value", &mixValue, 0, 1.0f);
	}

}