#include "SampleTextureMix.h"

#include "VertexBufferLayout.h"
#include "imgui/imgui.h"


namespace Sample
{
	SampleTextureMix::SampleTextureMix()
	{
		float position[] = 
		{
			-0.5f, -0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f, 2.0f, 0.0f,
			 0.5f,  0.5f, 2.0f, 2.0f,
			-0.5f,  0.5f, 0.0f, 2.0f,
		};

		unsigned int indexes[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		mixValue = 0.8f;

		vao = std::make_unique<VertexArray>();
		vbo = std::make_unique<VertexBuffer>(position, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		vao->AddBuffer(*vbo, layout);

		ibo = std::make_unique<IndexBuffer>(indexes, 6);

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
		renderer->Draw(*vao, *ibo, *shader);
	}

	void SampleTextureMix::OnImguiRender()
	{
		ImGui::SliderFloat("mix value", &mixValue, 0, 1.0f);
	}

}