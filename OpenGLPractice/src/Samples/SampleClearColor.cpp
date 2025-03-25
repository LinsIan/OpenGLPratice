#include "SampleClearColor.h"
#include "GL/glew.h"
#include "imgui/imgui.h"
#include "../Renderer.h"

namespace Sample
{
    SampleClearColor::SampleClearColor()
        : clearColor { 0.3f, 0.3f, 0.7f, 1.0f }
    {
    }
    
    SampleClearColor::~SampleClearColor()
    {
    }

    void SampleClearColor::OnUpdate(float deltaTime)
    {
    }
    
    void SampleClearColor::OnRender()
    {
        GLCall(glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
    }
    
    void SampleClearColor::OnImguiRender()
    {
        ImGui::ColorEdit4("Clear Color", clearColor);
    }
}