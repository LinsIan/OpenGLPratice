#pragma once

#include "Mesh.h"
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
    std::shared_ptr<Mesh::Mesh> model;
    std::shared_ptr<Material> material;
	std::shared_ptr<Material> outlineMaterial;
    std::unique_ptr<Transform> transform;
	bool isSelected = false;

public:
    GameObject()
    {
        model = nullptr;
        material = nullptr;
        outlineMaterial = nullptr;
        transform = std::make_unique<Transform>();
        isSelected = false;
    }

    GameObject(std::shared_ptr<Mesh::Mesh> modelptr, std::string shaderPath)
    {
        model = modelptr;
        material = std::make_shared<Material>(shaderPath);
        transform = std::make_unique<Transform>();
    }

    GameObject(std::shared_ptr<Mesh::Mesh> modelptr, std::shared_ptr<Material> materialPtr)
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
        material->BindTextures();
        material->GetShader().SetUniformMat4f("u_MVP", proj * view * transform->GetMatrix());
        material->GetShader().SetUniformMat4f("u_Model", transform->GetMatrix());
        material->GetShader().SetUniformMat3f("u_NormalMatrix", transform->GetNormalMatrix());

        if (outlineMaterial == nullptr || !isSelected)
        {
            glStencilMask(0x00);
            Renderer::Draw(model->GetVertexArray(), material->GetShader(), GetIndexCount());
		}
		else if (outlineMaterial != nullptr && isSelected)
        {
			// in Application.cpp, we have enabled stencil test and set the stencil operation to GL_KEEP, GL_KEEP, GL_REPLACE
            // glEnable(GL_STENCIL_TEST);
            // glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
            
			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glStencilMask(0xFF);
			Renderer::Draw(model->GetVertexArray(), material->GetShader(), GetIndexCount());
			glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
			glStencilMask(0x00);
			glDepthFunc(GL_ALWAYS);
			transform->GetScale() *= 1.1f;
            outlineMaterial->BindShader();
            outlineMaterial->GetShader().SetUniformMat4f("u_MVP", proj * view * transform->GetMatrix());
			Renderer::Draw(model->GetVertexArray(), outlineMaterial->GetShader(), GetIndexCount());
			glStencilMask(0xFF);
			glDepthFunc(GL_LESS);
			transform->GetScale() /= 1.1f;
        }
        
    }

    void OnRenderUBO() //temp method name
    {
        material->BindShader();
        material->BindTextures();
            material->GetShader().SetUniformMat4f("u_Model", transform->GetMatrix());
        material->GetShader().SetUniformMat3f("u_NormalMatrix", transform->GetNormalMatrix());

        if (outlineMaterial == nullptr || !isSelected)
        {
            glStencilMask(0x00);
            Renderer::Draw(model->GetVertexArray(), material->GetShader(), GetIndexCount());
		}
		else if (outlineMaterial != nullptr && isSelected)
        {
			// in Application.cpp, we have enabled stencil test and set the stencil operation to GL_KEEP, GL_KEEP, GL_REPLACE
            // glEnable(GL_STENCIL_TEST);
            // glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
            
			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glStencilMask(0xFF);
			Renderer::Draw(model->GetVertexArray(), material->GetShader(), GetIndexCount());
			glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
			glStencilMask(0x00);
			glDepthFunc(GL_ALWAYS);
			transform->GetScale() *= 1.1f;
            outlineMaterial->BindShader();
            outlineMaterial->GetShader().SetUniformMat4f("u_Model", transform->GetMatrix());
			Renderer::Draw(model->GetVertexArray(), outlineMaterial->GetShader(), GetIndexCount());
			glStencilMask(0xFF);
			glDepthFunc(GL_LESS);
			transform->GetScale() /= 1.1f;
        }
    }

    void SetOutlineMaterial(std::shared_ptr<Material> outlineMat)
    {
        outlineMaterial = outlineMat;
	}

    void SetIsSelected(bool selected)
    {
        isSelected = selected;
	}

    inline Mesh::Mesh& GetModel() const { return *model; }
    inline Material& GetMaterial() const { return *material; }
    inline Transform& GetTransform() const { return *transform; }
    inline unsigned int GetIndexCount() const { return model->GetIndexBuffer().GetCount(); }

};
