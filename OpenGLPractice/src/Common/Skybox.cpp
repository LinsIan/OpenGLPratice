#include "Skybox.h"
#include "Cube.h"

Skybox::Skybox(const std::vector<std::string>& faces)
{
    auto skyboxMaterial = std::make_shared<Material>("res/shaders/Skybox.shader");
    skyboxMaterial->AddTexture(faces, 0, "u_Cubemap");
    skyboxMaterial->BindTextures();
    model = std::make_shared<Mesh::Cube>(2.0f, 2.0f, 2.0f);
    material = skyboxMaterial;
}

void Skybox::OnRender()
{
    glDisable(GL_CULL_FACE);
    GLCall(glDepthFunc(GL_LEQUAL));
    GameObject::OnRender();
    GLCall(glDepthFunc(GL_LESS));
    glEnable(GL_CULL_FACE);
}
