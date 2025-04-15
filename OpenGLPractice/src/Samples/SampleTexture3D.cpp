#include "SampleTexture3D.h"
#include "GLFW/glfw3.h"
#include "Cube.h"

namespace Sample
{
	SampleTexture3D::SampleTexture3D()
	{
        glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        isShowCursor = true;

        auto material = std::make_shared<Material>("res/shaders/TextureMix.shader");
        material->AddTexture("res/textures/awesomeface.png", 0, "u_TextureA");
        material->AddTexture("res/textures/container.jpg", 1, "u_TextureB");
        material->BindTextures();
        material->GetShader().SetUniform1f("u_Degree", 0.8f);

		auto cube1 = std::make_unique<GameObject>(std::make_shared<Model::Cube>(1.0f, 1.0f, 1.0f), material);
        auto cube2 = std::make_unique<GameObject>(std::make_shared<Model::Cube>(1.2f, 1.2f, 1.2f), material);
        auto cube3 = std::make_unique<GameObject>(std::make_shared<Model::Cube>(0.6f, 0.8f, 1.4f), material);

        cubes.push_back(std::move(cube1));
        cubes.push_back(std::move(cube2));
        cubes.push_back(std::move(cube3));

		cubes[1]->GetTransform().SetTranslation(-1.3f, 0, -0.8f);
		cubes[1]->GetTransform().SetRotation(30, 34, -13);

		cubes[2]->GetTransform().SetTranslation(1.3f, 0, -0.6f);
		cubes[2]->GetTransform().SetRotation(-38, 60, 34);

		camera = std::make_unique<Camera>(CameraType::PERSPECTIVE, 960.0f, 540.0f);
	}

	SampleTexture3D::~SampleTexture3D()
	{
	}
 	
	void SampleTexture3D::OnUpdate(float deltaTime)
	{
		cubes[1]->GetTransform().GetRotation().y += 10 * deltaTime;
		cubes[2]->GetTransform().GetRotation().x += 10 * deltaTime;
	}

	void SampleTexture3D::OnRender()
	{
        for (auto& cube : cubes)
        {
            cube->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
        }
	}

	void SampleTexture3D::OnImguiRender()
	{
		ImGui::Text("Camera: Perspective");
        ImGui::Text("Press F to toggle mouse cursor");
		ImGui::SliderFloat3("Model translation A:", &cubes[0]->GetTransform().GetTranslation().x, -1.0f, 1.0f);
		ImGui::SliderFloat3("Model rotation:", &cubes[0]->GetTransform().GetRotation().x, 0.0f, 360.0f);
		ImGui::SliderFloat3("Model scale:", &cubes[0]->GetTransform().GetScale().x, 0.1f, 3.0f);


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