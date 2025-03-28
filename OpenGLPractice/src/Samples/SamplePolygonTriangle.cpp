#include "SamplePolygonTriangle.h"
#include "VertexBufferLayout.h"

Sample::SamplePolygonTriangle::SamplePolygonTriangle()
{
    float positionsA[] = {
         0.0f, -0.5f,
         1.0f, -0.5f,
         0.5f,  0.5f
    };

    unsigned int indicesA[] = {
        0, 1, 2
    };

    vertexArrayA = std::make_unique<VertexArray>();
    vertexBufferA = std::make_unique<VertexBuffer>(positionsA, 3 * 2 * sizeof(float));
    VertexBufferLayout layoutA;
    layoutA.Push<float>(2);
    vertexArrayA->AddBuffer(*vertexBufferA, layoutA);
    indexBufferA = std::make_unique<IndexBuffer>(indicesA, 3); // index buffer binding must be done after vertex buffer binding

    vertexArrayA->Unbind();
    vertexBufferA->Unbind();
    indexBufferA->Unbind();

    float positionsB[] = {
        -1.0f, -0.5f,
         0.0f, -0.5f,
        -0.5f,  0.5f,
    };

    unsigned int indicesB[] = {
        0, 1, 2
    };

    vertexArrayB = std::make_unique<VertexArray>();
    vertexBufferB = std::make_unique<VertexBuffer>(positionsB, 3 * 2 * sizeof(float));
    VertexBufferLayout layoutB;
    layoutB.Push<float>(2);
    vertexArrayB->AddBuffer(*vertexBufferB, layoutB);
    indexBufferB = std::make_unique<IndexBuffer>(indicesB, 3);

    vertexArrayB->Unbind();
    vertexBufferB->Unbind();
    indexBufferB->Unbind();

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
    renderer->Draw(*vertexArrayA, *indexBufferA, *shader);
    renderer->Draw(*vertexArrayB, *indexBufferB, *shader);
}
