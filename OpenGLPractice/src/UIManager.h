#pragma once

#include "Transform.h"
#include "Camera.h"
#include "imgui/imgui.h"
#include "GLFW/glfw3.h"

class UIManager
{
private:
    static bool isShowCursor;
    static ImVec2 lastMousePos;
    
public:
    static void ShowTransformUI(Transform &transform)
    {
        ImGui::SliderFloat3("Model translation A:", &transform.GetTranslation().x, -1.0f, 1.0f);
        ImGui::SliderFloat3("Model rotation:", &transform.GetRotation().x, 0.0f, 360.0f);
        ImGui::SliderFloat3("Model scale:", &transform.GetScale().x, 0.1f, 3.0f);
    }

    static void ShowCursorUI()
    {
        ImGui::Text("Press F to toggle mouse cursor");

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
    }

    static void ShowCameraUI(Camera& camera)
    {
        if (camera.GetCameraType() == CameraType::PERSPECTIVE)
            ImGui::Text("Camera: Perspective");
        else if (camera.GetCameraType() == CameraType::ORTHOGRAPHIC)
            ImGui::Text("Camera: Orthographic");

        if (isShowCursor) return;

        if (ImGui::IsKeyDown(ImGuiKey_W))
        {
            camera.MoveForward();
        }
        if (ImGui::IsKeyDown(ImGuiKey_S))
        {
            camera.MoveBackward();
        }
        if (ImGui::IsKeyDown(ImGuiKey_A))
        {
            camera.MoveLeft();
        }
        if (ImGui::IsKeyDown(ImGuiKey_D))
        {
            camera.MoveRight();
        }

        ImVec2 currentPos = ImGui::GetMousePos();

        if (currentPos.x != lastMousePos.x || currentPos.y != lastMousePos.y)
        {
            float xOffset = currentPos.x - lastMousePos.x;
            float yOffset = lastMousePos.y - currentPos.y;

            camera.Rotate(xOffset, yOffset);
            lastMousePos = currentPos;
        }

        float wheel = ImGui::GetIO().MouseWheel;

        if (wheel != 0.0f)
        {
            camera.SetFov(wheel);
        }
    }
};

bool UIManager::isShowCursor = true;
ImVec2 UIManager::lastMousePos = ImVec2(0.0f, 0.0f);