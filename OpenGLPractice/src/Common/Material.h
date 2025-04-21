#pragma once

#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "MaterialDatabase.h"

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

    void SetMaterialProperties(const MaterialProperties& material)
    {
        shader->SetUniform3f("material.ambient", material.ambient.x, material.ambient.y, material.ambient.z);
        shader->SetUniform3f("material.diffuse", material.diffuse.x, material.diffuse.y, material.diffuse.z);
        shader->SetUniform3f("material.specular", material.specular.x, material.specular.y, material.specular.z);
        shader->SetUniform1f("material.shininess", material.shininess);
    }

    void SetMaterialProperties(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess)
    {
        shader->SetUniform3f("material.ambient", ambient.x, ambient.y, ambient.z);
        shader->SetUniform3f("material.diffuse", diffuse.x, diffuse.y, diffuse.z);
        shader->SetUniform3f("material.specular", specular.x, specular.y, specular.z);
        shader->SetUniform1f("material.shininess", shininess);
    }

    void SetLightPos(const glm::vec3& lightPos)
    {
        shader->SetUniform3f("light.position", lightPos.x, lightPos.y, lightPos.z);
    }

    void SetLightColor(const glm::vec4 lightColor, glm::vec3 lightStrength)
    {
        shader->SetUniform3f("light.ambient", lightColor.r * lightStrength.x, lightColor.g * lightStrength.x, lightColor.b * lightStrength.x);
        shader->SetUniform3f("light.diffuse", lightColor.r * lightStrength.y, lightColor.g * lightStrength.y, lightColor.b * lightStrength.y);
        shader->SetUniform3f("light.specular", lightColor.r * lightStrength.z, lightColor.g * lightStrength.z, lightColor.b * lightStrength.z);
    }

    void SetViewPos(const glm::vec3& viewPos)
    {
        shader->SetUniform3f("u_ViewPos", viewPos.x, viewPos.y, viewPos.z);
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