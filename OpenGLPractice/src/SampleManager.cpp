#include "SampleManager.h"
#include "Rectangle.h"
#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "Samples/SampleClearColor.h"
#include "Samples/SamplePolygonTriangle.h"
#include "Samples/SampleRectangle.h"
#include "Samples/SampleTexture2D.h"
#include "Samples/SampleTextureMix.h"
#include "Samples/SampleTexture3D.h"
#include "Samples/SampleLightTest.h"
#include "Samples/SampleLightingMaps.h"
#include "Samples/SampleLightCaster.h"
#include "Samples/SampleMultiLight.h"
#include "Samples/SampleImportModel.h"
#include "Samples/SampleDepthTesting.h"

SampleManager::SampleManager()
{
    // Create and bind the framebuffer object
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    // Create a color texture attachment
    glGenTextures(1, &texColorBuffer);
    glBindTexture(GL_TEXTURE_2D, texColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1280, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Attach the color texture to the framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

    // Add a depth/stencil attachment using a renderbuffer (write-only, no sampling needed)
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1280, 720);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    // Verify the framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

    // Unbind so subsequent rendering targets the default framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    auto rect = std::make_shared<Mesh::Rectangle>(2.0f, 2.0f, 1.0f, 1.0f);
    auto texture = std::make_shared<Texture>(texColorBuffer);
    auto material = std::make_shared<Material>("res/shaders/Texture.shader");
    material->AddTexture(texture, 8, "u_Texture");
    material->BindTextures();
    screen = std::make_unique<GameObject>(rect, material);
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

            if (ImGui::MenuItem("LightingMaps"))
            {
                sample = nullptr;
                sample = std::make_unique<Sample::SampleLightingMaps>();
            }

            if (ImGui::MenuItem("LightCaster"))
            {
                sample = nullptr;
                sample = std::make_unique<Sample::SampleLightCaster>();
            }

            if (ImGui::MenuItem("MultiLight"))
            {
                sample = nullptr;
                sample = std::make_unique<Sample::SampleMultiLight>();
            }

            if (ImGui::MenuItem("ImportModel"))
            {
                sample = nullptr;
                sample = std::make_unique<Sample::SampleImportModel>();
            }

            if (ImGui::MenuItem("DepthTesting"))
            {
                sample = nullptr;
                sample = std::make_unique<Sample::SampleDepthTesting>();
			}

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
    
    if (!sample) return;
    
    sample->OnUpdate(0.05f);

    // draw to framebuffer
    glEnable(GL_DEPTH_TEST);
    glStencilMask(0xFF);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
    sample->OnRender();
    sample->OnImguiRender();

    // draw to default framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(1, 1, 1, 1);
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
    glDisable(GL_DEPTH_TEST);
    screen->GetMaterial().BindTextures();
    screen->OnRender(glm::mat4(1.0f), glm::mat4(1.0f));
}