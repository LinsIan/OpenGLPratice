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
			// �e��B�J�bApplication.cpp���w�]�w
            // �ҥμҪO�w��
            // glEnable(GL_STENCIL_TEST);
			// �]�w���q�L�B�q�L�ɪ��ާ@�AGL_REPLACE�N���ref�ȴ����ҪO�w�Ī���
            // glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
            
			// �]�w�q�L����Bref�ȡB�B�n
			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			// �ҥμg�J�ҪO�w��
			glStencilMask(0xFF);
            // ø�s����
			Renderer::Draw(model->GetVertexArray(), material->GetShader(), GetIndexCount());
			// ��g�q�L���󬰤�����1
			glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
			// �T��g�J�ҪO�w��
			glStencilMask(0x00);
			// �����`�״��աA�קK�����Q�B��
			glDisable(GL_DEPTH_TEST);
			// ��j����Hø�s����
			transform->GetScale() *= 1.1f;
            outlineMaterial->BindShader();
            outlineMaterial->GetShader().SetUniformMat4f("u_MVP", proj * view * transform->GetMatrix());
			// ø�s����
			Renderer::Draw(model->GetVertexArray(), outlineMaterial->GetShader(), GetIndexCount());
			// �}�Ҽg�J�ҪO�w�ġA�קKglClear�M����
			glStencilMask(0xFF);
			// ���s�}�Ҳ`�״���
			glEnable(GL_DEPTH_TEST);
			// ����j�p�٭�
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
