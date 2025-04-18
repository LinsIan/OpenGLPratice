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

in vec3 v_Normal;
in vec3 v_FragPos;

layout(location = 0) out vec4 color;

uniform vec4 u_Color;
uniform vec3 u_LightColor;
uniform vec3 u_LightPos;
uniform vec3 u_ViewPos;
uniform mat3 u_NormalMatrix;

float ambientStrength = 0.1f;
float specularStrength = 0.5f;
vec3 normal;
vec3 lightDir;

vec3 CalcAmbient()
{
    return ambientStrength * u_LightColor;
}

vec3 CalcDiffuse()
{
    normal = normalize(u_NormalMatrix * v_Normal);
    lightDir = normalize(u_LightPos - v_FragPos);

    float diff = max(dot(normal, lightDir), 0.0);
    return diff * u_LightColor;
}

vec3 CalcSpecular()
{
    vec3 viewDir = normalize(u_ViewPos - v_FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    return specularStrength * spec * u_LightColor;
}

void main()
{
    color = vec4(CalcAmbient() + CalcDiffuse() + CalcSpecular(), 1.0f) * u_Color ;
}
