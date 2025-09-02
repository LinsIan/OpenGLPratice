#pragma once

#include "Model.h"
#include "Material.h"
#include "Transform.h"
#include "Renderer.h"
#include "Camera.h"
#include "glm/glm.hpp"

#include <memory>
#include <string>

class GameObject
{
protected:
    std::shared_ptr<Model::Model> model;
    std::shared_ptr<Material> material;
    std::unique_ptr<Transform> transform;

public:
    GameObject()
    {
        model = nullptr;
        material = nullptr;
        transform = std::make_unique<Transform>();
    }

    GameObject(std::shared_ptr<Model::Model> modelptr, std::string shaderPath)
    {
        model = modelptr;
        material = std::make_shared<Material>(shaderPath);
        transform = std::make_unique<Transform>();
    }

    GameObject(std::shared_ptr<Model::Model> modelptr, std::shared_ptr<Material> materialPtr)
    {
        model = modelptr;
        material = materialPtr;
        transform = std::make_unique<Transform>();
    }

    virtual ~GameObject() {}

    virtual void OnUpdate(float deltaTime) {}

    void OnRender() 
    {
        Renderer::Draw(model->GetVertexArray(),  material->GetShader(), model->GetIndexBuffer().GetCount());
    }

    void OnRender(const glm::mat4& proj, const glm::mat4& view)
    {
        material->BindShader();
        material->GetShader().SetUniformMat4f("u_MVP", proj * view * transform->GetMatrix());
        material->GetShader().SetUniformMat4f("u_Model", transform->GetMatrix());
        Renderer::Draw(model->GetVertexArray(), material->GetShader(), GetIndexCount());
    }

    inline Model::Model& GetModel() const { return *model; }
    inline Material& GetMaterial() const { return *material; }
    inline Transform& GetTransform() const { return *transform; }
    inline unsigned int GetIndexCount() const { return model->GetIndexBuffer().GetCount(); }

};
