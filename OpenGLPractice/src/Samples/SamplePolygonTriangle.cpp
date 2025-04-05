#include "SamplePolygonTriangle.h"
#include "VertexBufferLayout.h"

Sample::SamplePolygonTriangle::SamplePolygonTriangle()
{
    triangleA = std::make_unique<Model::Triangle>(0.0f, 1.0f, 1.0f);
    triangleB = std::make_unique<Model::Triangle>(-1.0f, 0.0f, 1.0f);

    shader = std::make_unique<Shader>("res/shaders/Basic.shader");
    shader->Bind();
    shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    renderer = std::make_unique<Renderer>();
}

Sample::SamplePolygonTriangle::~SamplePolygonTriangle()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Sample::SamplePolygonTriangle::OnRender()
{
    renderer->Draw(triangleA->GetVertexArray(), triangleA->GetIndexBuffer(), *shader);
    renderer->Draw(triangleB->GetVertexArray(), triangleB->GetIndexBuffer(), *shader);
}
