#pragma once
#include "GameObject.h"
#include "Sphere.h"
#include "LightProperties.h"

#include <memory>
#include <type_traits>

enum class LightType
{
	POINT,
	DIRECTIONAL,
	SPOT
};

template<typename T>
struct is_valid_light_type : std::false_type {};

template<> struct is_valid_light_type<BaseLightProperties> : std::true_type {};
template<> struct is_valid_light_type<DirLightProperties> : std::true_type {};
template<> struct is_valid_light_type<PointLightProperties> : std::true_type {};
template<> struct is_valid_light_type<SpotLightProperties> : std::true_type {};

template<typename T, typename = typename std::enable_if<is_valid_light_type<T>::value>::type>
class Light : public GameObject
{
private: 
	LightType lightType;
	T lightProperties;

	void Init()
	{
		material = std::make_shared<Material>("res/shaders/Basic3D.shader");
		model = std::make_shared<Mesh::Sphere>(0.2f, 20, 20);
        InitImpl(typename light_type<T>::tag());
	}

    void InitImpl(position_light_tag)
    {
		material->SetColor(lightProperties.specular);
		transform->SetTranslation(lightProperties.position.x, lightProperties.position.y, lightProperties.position.z);
    }

    void InitImpl(dir_light_tag)
    {
    }

public:
	Light(LightType type, T properties)
		: lightType(type), lightProperties(properties)
	{
		Init();
	}

	~Light() {}

	void OnUpdate(float deltaTime) override
	{ 
        OnUpdateImpl(typename light_type<T>::tag());
	}

    void OnUpdateImpl(position_light_tag)
    {
		lightProperties.position = transform->GetTranslation();
    }

	void OnUpdateImpl(dir_light_tag){}

	LightType GetLightType() const { return lightType; }
    T& GetLightProperties() { return lightProperties; }
};
