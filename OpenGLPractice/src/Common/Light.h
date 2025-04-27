#pragma once
#include "GameObject.h"
#include "Sphere.h"
#include "LightProperties.h"

#include <memory>

enum class LightType
{
	POINT,
	DIRECTIONAL,
	SPOT
};

class Light : public GameObject
{
private: 
	LightType lightType;
	LightProperties lightProperties;

	void Init()
	{
		switch (lightType)
		{
		case LightType::DIRECTIONAL:
			break;
		case LightType::POINT:
		case LightType::SPOT:
			material = std::make_shared<Material>("res/shaders/Basic3D.shader");
			model = std::make_shared<Model::Sphere>(0.2f, 20, 20);
			material->SetColor(lightProperties.diffuse);
			break;
		default:
			break;
		}

		transform->SetTranslation(lightProperties.position.x, lightProperties.position.y, lightProperties.position.z);
	}

public:
	Light(LightType type, const glm::vec3& position, const glm::vec3& direction,
		const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
		: lightType(type), lightProperties{ position, direction, ambient, diffuse, specular }
	{
		Init();
	}

	Light(LightType type, LightProperties properties)
		: lightType(type), lightProperties(properties)
	{
		Init();
	}

	~Light() {}

	void OnUpdate(float deltaTime) override
	{
		lightProperties.position = transform->GetTranslation();
	}

	LightType GetLightType() const { return lightType; }
	LightProperties& GetLightProperties() { return lightProperties; }

};

