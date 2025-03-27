#include "SampleClearColor.h"
#include "imgui/imgui.h"
#include "Renderer.h"

namespace Sample
{
    SampleClearColor::SampleClearColor()
        : clearColor { 0.3f, 0.3f, 0.7f, 1.0f }
    {
    }
    
    SampleClearColor::~SampleClearColor()
    {
        GLCall(glClearColor(0, 0, 0, 1));
    }

    void SampleClearColor::OnUpdate(float deltaTime)
    {
    }
    
    void SampleClearColor::OnRender()
    {
        GLCall(glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]));
    }
    
    void SampleClearColor::OnImguiRender()
    {
        ImGui::ColorEdit4("Clear Color", clearColor);
    }
}