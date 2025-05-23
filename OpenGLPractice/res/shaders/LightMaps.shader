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

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_FragPos;

uniform Material material;
uniform Light light;
uniform vec3 u_ViewPos;
uniform mat3 u_NormalMatrix;

vec3 CalcAmbient()
{
    return light.ambient * texture(material.diffuse, v_TexCoord).rgb;
}

vec3 CalcDiffuse(vec3 normal, vec3 lightDir)
{
    float diff = max(dot(normal, lightDir), 0.0);
    return light.diffuse * (diff * texture(material.diffuse, v_TexCoord).rgb);
}

vec3 CalcSpecular(vec3 normal, vec3 lightDir)
{
    vec3 viewDir = normalize(u_ViewPos - v_FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    return light.specular * (spec * texture(material.specular, v_TexCoord).rgb);
}

void main()
{
    vec3 normal = normalize(u_NormalMatrix * v_Normal);
    vec3 lightDir = normalize(light.position - v_FragPos);

    color = vec4(CalcAmbient() + CalcDiffuse(normal, lightDir) + CalcSpecular(normal, lightDir), 1.0);
}