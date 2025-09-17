#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec2 v_TexCoord;
out vec3 v_Normal;
out vec3 v_FragPos;

uniform mat4 u_MVP;
uniform mat4 u_Model;

void main()
{
    gl_Position = u_MVP * position;
    v_TexCoord = texCoord;
    v_Normal = normal;
    v_FragPos = vec3(u_Model * position);
}

#shader fragment
#version 330 core

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct PointLight {
    vec3 position;  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_FragPos;

uniform Material material;
uniform PointLight pointLight;
uniform vec3 u_ViewPos;
uniform mat3 u_NormalMatrix

vec3 CalPointLight(vec3 normal, vec3 lightDir, vec3 viewDir)
{

}

void main()
{
    vec3 normal = normalize(u_NormalMatrix * v_Normal);
    vec3 lightDir = normalize(pointLight.position - v_FragPos);
    vec3 viewDir = normalize(u_ViewPos - v_FragPos);

    corlo = vec4(CalPointLight(normal, lightDir, viewDir), 1.0);
}