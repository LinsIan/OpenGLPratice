#pragma once

#include "Transform.h"
#include "Camera.h"
#include "imgui/imgui.h"
#include "GLFW/glfw3.h"

class UIManager
{
private:    
    static UIManager* instance;
    bool isShowCursor = true;
    ImVec2 lastMousePos = ImVec2(0.0f, 0.0f);
    
public:
    static UIManager* GetInstance()
    {
        if (instance == nullptr)
        {
            instance = new UIManager();
        }
        return instance;
    }

    static void ShowTransformUI(std::string Name, Transform &transform, float maxTranslation = 1.0f)
    {
        ImGui::Text("%s :", Name.c_str());
        ImGui::SliderFloat3("translation:",  &transform.GetTranslation().x, -maxTranslation, maxTranslation);
        ImGui::SliderFloat3("rotation:", &transform.GetRotation().x, 0.0f, 360.0f);
        ImGui::SliderFloat3("scale:", &transform.GetScale().x, 0.1f, 3.0f);
    }

    void ShowCursorUI()
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

    void ShowCameraUI(Camera& camera)
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
