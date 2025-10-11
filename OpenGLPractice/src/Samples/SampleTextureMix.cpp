#include "SampleTextureMix.h"

#include "imgui/imgui.h"
#include "Rectangle.h"


namespace Sample
{
	SampleTextureMix::SampleTextureMix()
	{
		mixValue = 0.8f;

		auto rect = std::make_shared<Mesh::Rectangle>(1.0f, 1.0f, 2.0f, 2.0f);

		filteringMode = GL_LINEAR; // GL_NEAREST
		wrappingMode = GL_REPEAT; // GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER, GL_REPEAT, GL_MIRRORED_REPEAT

		auto material = std::make_shared<Material>("res/shaders/TextureMix.shader");
		material->BindShader();
		material->AddTexture("res/textures/awesomeface.png", 0, "u_TextureA", filteringMode, wrappingMode);
		material->AddTexture("res/textures/container.jpg", 1, "u_TextureB", filteringMode, wrappingMode);
		material->BindTextures();

		material->GetShader().SetUniformMat4f("u_MVP", glm::mat4(1.0f));
		material->GetShader().SetUniform1f("u_Degree", mixValue);

        rectangle = std::make_unique<GameObject>(rect, material);
	}

	SampleTextureMix::~SampleTextureMix()
	{
	}

	void SampleTextureMix::OnRender()
	{
		rectangle->GetMaterial().GetShader().SetUniform1f("u_Degree", mixValue);
        rectangle->OnRender();
	}

	void SampleTextureMix::OnImguiRender()
	{
		ImGui::SliderFloat("mix value", &mixValue, 0, 1.0f);
	}

}