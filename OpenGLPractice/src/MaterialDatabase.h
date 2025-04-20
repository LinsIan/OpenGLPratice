#pragma once

#include "glm/glm.hpp"
#include <map>
#include <string>

enum MaterialType
{
	Emerald,
	Jade,
	Obsidian,
	Pearl,
	Ruby,
	Turquoise,
	Brass,
	Bronze,
	Chrome,
	Copper,
	Gold,
	Silver,
	BlackPlastic,
	CyanPlastic,
	GreenPlastic,
	RedPlastic,
	WhitePlastic,
	YellowPlastic,
	BlackRubber,
	CyanRubber,
	GreenRubber,
	RedRubber,
	WhiteRubber,
	YellowRubber
};

std::string MaterialTypeToString(MaterialType type);

struct MaterialProperties
{
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};

class MaterialDatabase
{
private:
	std::map<MaterialType, MaterialProperties> materialProperties;

public:
	MaterialDatabase();
	~MaterialDatabase();

	MaterialProperties GetMaterialProperties(MaterialType type)
	{
		return materialProperties[type];
	}

	std::map<MaterialType, MaterialProperties> GetAllMaterialProperties()
	{
		return materialProperties;
	}
};
