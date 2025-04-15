#include "SampleManager.h"
#include "imgui/imgui.h"
#include "Samples/SampleClearColor.h"
#include "Samples/SamplePolygonTriangle.h"
#include "Samples/SampleRectangle.h"
#include "Samples/SampleTexture2D.h"
#include "Samples/SampleTextureMix.h"
#include "Samples/SampleTexture3D.h"
#include "Samples/SampleLightTest.h"

SampleManager::SampleManager()
{
}

SampleManager::~SampleManager()
{
}

void SampleManager::OnUpdate()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Samples"))
        {
            if (ImGui::MenuItem("ClearColor"))
            {
                sample = nullptr;
                sample = std::make_unique<Sample::SampleClearColor>();
            }

            if (ImGui::MenuItem("PolugonTriangle"))
            {
                sample = nullptr;
                sample = std::make_unique<Sample::SamplePolygonTriangle>();
            }

            if (ImGui::MenuItem("Rectangle"))
            {
                sample = nullptr;
                sample = std::make_unique<Sample::SampleRectangle>();
            }

            if (ImGui::MenuItem("Texture2D"))
            {
                sample = nullptr;
                sample = std::make_unique<Sample::SampleTexture2D>();
            }

            if (ImGui::MenuItem("Texture2D Mix"))
            {
                sample = nullptr;
                sample = std::make_unique<Sample::SampleTextureMix>();
            }

            if (ImGui::MenuItem("Texture3D"))
            {
                sample = nullptr;
                sample = std::make_unique<Sample::SampleTexture3D>();
            }

            if (ImGui::MenuItem("LightTest"))
            {
                sample = nullptr;
                sample = std::make_unique<Sample::SampleLightTest>();
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
    
    if (!sample) return;
    
    sample->OnUpdate(0.05f);
    sample->OnRender();
    sample->OnImguiRender();
}