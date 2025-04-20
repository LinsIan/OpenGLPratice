#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

uniform mat4 u_MVP;
uniform mat4 u_Model;

out vec3 v_Normal;
out vec3 v_FragPos;

void main()
{
    gl_Position = u_MVP * position;
    v_FragPos = vec3(u_Model * position);
    v_Normal = normal;
}

#shader fragment
#version 330 core

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 v_Normal;
in vec3 v_FragPos;

layout(location = 0) out vec4 color;

uniform Material material;
uniform Light light;
uniform vec4 u_Color;
uniform vec3 u_ViewPos;
uniform mat3 u_NormalMatrix;

vec3 normal;
vec3 lightDir;

vec3 CalcAmbient()
{
    return light.ambient * material.ambient;
}

vec3 CalcDiffuse()
{
    normal = normalize(u_NormalMatrix * v_Normal);
    lightDir = normalize(light.position - v_FragPos);

    float diff = max(dot(normal, lightDir), 0.0);
    return light.diffuse * (diff * material.diffuse);
}

vec3 CalcSpecular()
{
    vec3 viewDir = normalize(u_ViewPos - v_FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess *  128.0f);
    return light.specular * (spec * material.specular);
}

void main()
{
    color = vec4(CalcAmbient() + CalcDiffuse() + CalcSpecular(), 1.0f) * u_Color ;
}
