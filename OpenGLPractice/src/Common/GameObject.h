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
			// 前兩步驟在Application.cpp中已設定
            // 啟用模板緩衝
            // glEnable(GL_STENCIL_TEST);
			// 設定不通過、通過時的操作，GL_REPLACE代表用ref值替換模板緩衝的值
            // glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
            
			// 設定通過條件、ref值、遮罩
			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			// 啟用寫入模板緩衝
			glStencilMask(0xFF);
            // 繪製物體
			Renderer::Draw(model->GetVertexArray(), material->GetShader(), GetIndexCount());
			// 改寫通過條件為不等於1
			glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
			// 禁止寫入模板緩衝
			glStencilMask(0x00);
			// 關閉深度測試，避免輪廓被遮擋
			glDisable(GL_DEPTH_TEST);
			// 放大物體以繪製輪廓
			transform->GetScale() *= 1.1f;
            outlineMaterial->BindShader();
            outlineMaterial->GetShader().SetUniformMat4f("u_MVP", proj * view * transform->GetMatrix());
			// 繪製輪廓
			Renderer::Draw(model->GetVertexArray(), outlineMaterial->GetShader(), GetIndexCount());
			// 開啟寫入模板緩衝，避免glClear清不掉
			glStencilMask(0xFF);
			// 重新開啟深度測試
			glEnable(GL_DEPTH_TEST);
			// 物體大小還原
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
