#pragma once
#include "glm/glm.hpp"

struct BaseLightProperties
{
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

struct DirLightProperties
{
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct PointLightProperties
{
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

struct SpotLightProperties
{
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
	float constant;
    float linear;
    float quadratic;
    float cutOff;
	float outerCutOff;
};

struct position_light_tag {};
struct dir_light_tag {};

template<typename T> struct light_type;

template<> struct light_type<BaseLightProperties> {
    typedef position_light_tag tag;
};

template<> struct light_type<PointLightProperties> {
    typedef position_light_tag tag;
};

template<> struct light_type<DirLightProperties> {
    typedef dir_light_tag tag;
};

template<> struct light_type<SpotLightProperties> {
    typedef position_light_tag tag;
};