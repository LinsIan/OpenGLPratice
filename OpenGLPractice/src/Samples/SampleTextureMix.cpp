#include "SampleTextureMix.h"

#include "VertexBufferLayout.h"
#include "imgui/imgui.h"


namespace Sample
{
	SampleTextureMix::SampleTextureMix()
	{
		mixValue = 0.8f;

		rectangle = std::make_unique<Model::Rectangle>(1.0f, 1.0f, 2.0f, 2.0f);

		filteringMode = GL_LINEAR; // GL_NEAREST
		wrappingMode = GL_REPEAT; // GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER, GL_REPEAT, GL_MIRRORED_REPEAT
		textureSmile = std::make_unique<Texture>("res/textures/awesomeface.png", filteringMode, wrappingMode);
		textureBox = std::make_unique<Texture>("res/textures/container.jpg", filteringMode, wrappingMode);

		textureSmile->Bind(0);
		textureBox->Bind(1);

		shader = std::make_unique<Shader>("res/shaders/TextureMix.shader");
		shader->Bind();
		shader->SetUniform1i("u_TextureA", 0);
		shader->SetUniform1i("u_TextureB", 1);
		shader->SetUniform1f("u_Degree", mixValue);
		
		renderer = std::make_unique<Renderer>();
	}

	SampleTextureMix::~SampleTextureMix()
	{
	}

	void SampleTextureMix::OnRender()
	{
		shader->SetUniform1f("u_Degree", mixValue);
		renderer->Draw(rectangle->GetVertexArray(), rectangle->GetIndexBuffer(), *shader);
	}

	void SampleTextureMix::OnImguiRender()
	{
		ImGui::SliderFloat("mix value", &mixValue, 0, 1.0f);
	}

}