#pragma once

#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "MaterialDatabase.h"
#include "LightProperties.h"

#include <iostream>
#include <memory>
#include <map>
#include <string>

class Material
{
private:
    std::unique_ptr<Shader> shader;
    std::map<unsigned int, std::unique_ptr<Texture>> textures;

    glm::vec4 color;
public:
    Material(std::string shaderPath)
    {
        shader = std::make_unique<Shader>(shaderPath);
        shader->Bind();
        SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    }

    ~Material() {}

    void SetColor(float r, float g, float b, float a)
    {
        color = glm::vec4(r, g, b, a);
        shader->SetUniform4f("u_Color", color.r, color.g, color.b, color.a);
    }

    void SetColor(const glm::vec4& color)
    {
        this->color = color;
        shader->SetUniform4f("u_Color", color.r, color.g, color.b, color.a);
    }

	void SetColor(const glm::vec3& color, float a = 1.0f)
	{
		this->color = glm::vec4(color, a);
		shader->SetUniform4f("u_Color", color.r, color.g, color.b, a);
	}

    void SetMaterialProperties(const MaterialProperties& material)
    {
        shader->SetUniform3f("material.ambient", material.ambient.x, material.ambient.y, material.ambient.z);
        shader->SetUniform3f("material.diffuse", material.diffuse.x, material.diffuse.y, material.diffuse.z);
        shader->SetUniform3f("material.specular", material.specular.x, material.specular.y, material.specular.z);
        shader->SetUniform1f("material.shininess", material.shininess);
    }

    void SetMaterialAmbient(const glm::vec3& ambient)
    {
        shader->SetUniform3f("material.ambient", ambient.x, ambient.y, ambient.z);
    }

    void SetMaterialDiffuse(const glm::vec3& diffuse)
    {
        shader->SetUniform3f("material.diffuse", diffuse.x, diffuse.y, diffuse.z);
    }

    void SetMaterialSpecular(const glm::vec3& specular)
    {
        shader->SetUniform3f("material.specular", specular.x, specular.y, specular.z);
    }

    void SetMaterialShininess(float shininess)
    {
        shader->SetUniform1f("material.shininess", shininess);
    }

	void SetDirLightProperties(const DirLightProperties& lightProperties)
    {
		shader->SetUniform3f("dirLight.direction", lightProperties.direction);
		shader->SetUniform3f("dirLight.ambient", lightProperties.ambient);
		shader->SetUniform3f("dirLight.diffuse", lightProperties.diffuse);
		shader->SetUniform3f("dirLight.specular", lightProperties.specular);
    }

	void SetPointLightProperties(const PointLightProperties& lightProperties)
	{
		shader->SetUniform3f("pointLight.position", lightProperties.position);
		shader->SetUniform3f("pointLight.ambient", lightProperties.ambient);
		shader->SetUniform3f("pointLight.diffuse", lightProperties.diffuse);
		shader->SetUniform3f("pointLight.specular", lightProperties.specular);
		shader->SetUniform1f("pointLight.constant", lightProperties.constant);
		shader->SetUniform1f("pointLight.linear", lightProperties.linear);
		shader->SetUniform1f("pointLight.quadratic", lightProperties.quadratic);
	}

    void SetLightPos(const glm::vec3& lightPos)
    {
        shader->SetUniform3f("light.position", lightPos.x, lightPos.y, lightPos.z);
    }

    void SetLightProperties(const BaseLightProperties& lightProperties)
    {
		shader->SetUniform3f("light.position", lightProperties.position);
		shader->SetUniform3f("light.ambient", lightProperties.ambient);
		shader->SetUniform3f("light.diffuse", lightProperties.diffuse);
		shader->SetUniform3f("light.specular", lightProperties.specular);
    }

    void SetViewPos(const glm::vec3& viewPos)
    {
        shader->SetUniform3f("u_ViewPos", viewPos.x, viewPos.y, viewPos.z);
    }

	void UpdateBasicLightUniforms(const BaseLightProperties lightProperties, const glm::vec3& viewPos, const glm::mat4& normalMatrix)
    {
		shader->Bind();
        SetLightProperties(lightProperties);
        SetViewPos(viewPos);
        SetNormalMatrix(normalMatrix);
	}   

    void UpdateDirLightUniforms(const DirLightProperties &lightProperties, const glm::vec3& viewPos, const glm::mat4& normalMatrix)
    {
        shader->Bind();
        SetDirLightProperties(lightProperties);
        SetViewPos(viewPos);
        SetNormalMatrix(normalMatrix);
    }

    void UpdatePointLightUniforms(const PointLightProperties& lightProperties, const glm::vec3& viewPos, const glm::mat4& normalMatrix)
    {
        shader->Bind();
        SetPointLightProperties(lightProperties);
        SetViewPos(viewPos);
        SetNormalMatrix(normalMatrix);
    }

    void SetNormalMatrix(const glm::mat3& normalMatrix)
    {
        shader->SetUniformMat3f("u_NormalMatrix", normalMatrix);
    }

    void AddTexture(const std::string& path, unsigned int slot, std::string uniformName, int filtering = GL_LINEAR, int wrapping = GL_CLAMP_TO_EDGE)
    {
        textures[slot] = std::make_unique<Texture>(path, filtering, wrapping);
        textures[slot]->Bind(slot);
        shader->SetUniform1i(uniformName, slot);
    }

	void BindTextures()
	{
		for (auto& texture : textures)
		{
			texture.second->Bind(texture.first);
		}
	}

    void BindShader()
    {
        shader->Bind();
    }

    void UnbindShader()
    {
        shader->Unbind();
    }

    inline Shader& GetShader() const { return *shader.get(); }
    inline glm::vec4 GetColor() const { return color; }
};