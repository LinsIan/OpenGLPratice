#pragma once

#include "Shader.h"
#include "Texture.h"

#include <memory>
#include <map>
#include <string>

class Material
{
private:
    std::unique_ptr<Shader> shader;
    std::map<unsigned int, std::unique_ptr<Texture>> textures;    
public:
    Material(std::string shaderPath)
    {
        shader = std::make_unique<Shader>(shaderPath);
        shader->Bind();
    }
    ~Material() {}

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
};