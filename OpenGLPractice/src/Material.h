#pragma once

#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"

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