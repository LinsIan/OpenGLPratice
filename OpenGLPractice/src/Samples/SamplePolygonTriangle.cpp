#include "SamplePolygonTriangle.h"
#include "VertexBufferLayout.h"
#include "Triangle.h"


Sample::SamplePolygonTriangle::SamplePolygonTriangle()
{
    auto triA = std::make_shared<Model::Triangle>(0.0f, 1.0f, 1.0f);
    auto triB = std::make_shared<Model::Triangle>(-1.0f, 0.0f, 1.0f);
    auto material = std::make_shared<Material>("res/shaders/Basic.shader");

    triangleA = std::make_unique<GameObject>(triA, material);
    triangleB = std::make_unique<GameObject>(triB, material);

    material->GetShader().SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

    Renderer::SetPolygonMode(GL_LINE);
}

Sample::SamplePolygonTriangle::~SamplePolygonTriangle()
{
    Renderer::SetPolygonMode(GL_FILL);
}

void Sample::SamplePolygonTriangle::OnRender()
{
    triangleA->OnRender();
    triangleB->OnRender();
}
