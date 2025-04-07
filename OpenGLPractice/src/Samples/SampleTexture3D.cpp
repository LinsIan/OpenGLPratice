#include "SampleTexture3D.h"
#include "GLFW/glfw3.h"

namespace Sample
{
	SampleTexture3D::SampleTexture3D()
	{
        glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        isShowCursor = true;

		cubes.push_back(std::make_unique<Model::Cube>(1.0f, 1.0f, 1.0f, 1.0f, 1.0f));

		cubes.push_back(std::make_unique<Model::Cube>(1.2f, 1.2f, 1.2f, -1.0f, -1.0f));
		cubes[1]->SetTranslation(-1.3f, 0, -0.8f);
		cubes[1]->SetRotation(30, 34, -13);

		cubes.push_back(std::make_unique<Model::Cube>(0.6f, 0.8f, 1.4f, -1.0f, 1.0f));
		cubes[2]->SetTranslation(1.3f, 0, -0.6f);
		cubes[2]->SetRotation(-38, 60, 34);

		camera = std::make_unique<Camera>(CameraType::PERSPECTIVE, 960.0f, 540.0f);

		material = std::make_unique<Material>("res/shaders/TextureMix.shader");
		material->AddTexture("res/textures/awesomeface.png", 0, "u_TextureA");
		material->AddTexture("res/textures/container.jpg", 1, "u_TextureB");
		material->BindTextures();
		material->GetShader().SetUniform1f("u_Degree", 0.8f);

		renderer = std::make_unique<Renderer>();
	}

	SampleTexture3D::~SampleTexture3D()
	{
	}
 	
	void SampleTexture3D::OnUpdate(float deltaTime)
	{
		cubes[1]->GetRotation().y += 10 * deltaTime;
		cubes[2]->GetRotation().x += 10 * deltaTime;
	}

	void SampleTexture3D::OnRender()
	{
		glm::mat4 mvp(1.0f);

		for (auto& cube : cubes)
		{
			mvp = camera->GetProjectionMatrix() * camera->GetViewMatrix() * cube->GetModelMatrix();
			material->GetShader().SetUniformMat4f("u_MVP", mvp);
			renderer->Draw(cube->GetVertexArray(), cube->GetIndexBuffer(), material->GetShader());
		}
	}

	void SampleTexture3D::OnImguiRender()
	{
		ImGui::Text("Camera: Perspective");
        ImGui::Text("Press F to toggle mouse cursor");
		ImGui::SliderFloat3("Model translation A:", &cubes[0]->GetTranslation().x, -1.0f, 1.0f);
		ImGui::SliderFloat3("Model rotation:", &cubes[0]->GetRotation().x, 0.0f, 360.0f);
		ImGui::SliderFloat3("Model scale:", &cubes[0]->GetScale().x, 0.1f, 3.0f);


        if (ImGui::IsKeyPressed(ImGuiKey_F))
        {
            isShowCursor = !isShowCursor;

            if (isShowCursor)
			{
                glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
			else
			{
				glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				lastMousePos = ImGui::GetMousePos();
			}
        }

		if (isShowCursor) return;

		if (ImGui::IsKeyDown(ImGuiKey_W))
		{
			camera->MoveForward();
		}
		if (ImGui::IsKeyDown(ImGuiKey_S))
		{
			camera->MoveBackward();
		}
		if (ImGui::IsKeyDown(ImGuiKey_A))
		{
			camera->MoveLeft();
		}
		if (ImGui::IsKeyDown(ImGuiKey_D))
		{
			camera->MoveRight();
		}

		ImVec2 currentPos = ImGui::GetMousePos();

        if (currentPos.x != lastMousePos.x || currentPos.y != lastMousePos.y)
        {
            float xOffset = currentPos.x - lastMousePos.x;
            float yOffset = lastMousePos.y - currentPos.y;

			camera->Rotate(xOffset, yOffset);
            lastMousePos = currentPos;
        }

		float wheel = ImGui::GetIO().MouseWheel;

		if (wheel != 0.0f)
		{
			camera->SetFov(wheel);
		}


	}
}