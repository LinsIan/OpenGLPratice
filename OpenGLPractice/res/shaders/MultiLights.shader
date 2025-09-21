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

struct DirLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
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

struct SpotLight
{
	vec3 position;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float constant;
    float linear;
    float quadratic;
	float cutOff;
	float outerCutOff;
};

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_FragPos;

#define MAX_POINT_LIGHTS 12

uniform Material material;
uniform DirLight dirLight;
uniform int numPointLights;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform vec3 u_ViewPos;
uniform mat3 u_NormalMatrix;


vec3 CalDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 diffTex, vec3 specTex)
{
    // ambient
    vec3 ambient = light.ambient * diffTex;

    // diffuse
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * diffTex;

    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * specTex;

    return ambient + diffuse + specular;
}

vec3 CalPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 diffTex, vec3 specTex)
{
    // Ambient
    vec3 ambient = light.ambient * diffTex;

    // Diffuse
    vec3 lightDir = normalize(light.position - v_FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * diffTex;

    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * specTex;

    // Attenuation
    float distance = length(light.position - v_FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    return (ambient + diffuse + specular) * attenuation;
}

vec3 CalSpotLight(SpotLight light, vec3 normal, vec3 viewDir, vec3 diffTex, vec3 specTex)
{
    vec3 lightDir = normalize(spotLight.position - v_FragPos);
    float theta = dot(lightDir, normalize(-spotLight.direction));
	float epsilon = spotLight.cutOff - spotLight.outerCutOff;
	float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);
    
    // Ambient
	vec3 ambient = spotLight.ambient * texture(material.diffuse, v_TexCoord).rgb;

	// Diffuse
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = spotLight.diffuse * diff * texture(material.diffuse, v_TexCoord).rgb;
	diffuse *= intensity;

	// Specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = spotLight.specular * spec * texture(material.specular, v_TexCoord).rgb;
	specular *= intensity;

	// Attenuation
	float distance = length(spotLight.position - v_FragPos);
	float attenuation = 1.0 / (spotLight.constant + spotLight.linear * distance + spotLight.quadratic * (distance * distance));

	return (ambient + diffuse + specular) * attenuation;
}

void main()
{
    vec3 normal = normalize(u_NormalMatrix * v_Normal);
    vec3 viewDir = normalize(u_ViewPos - v_FragPos);
    vec3 diffTex = texture(material.diffuse, v_TexCoord).rgb;
    vec3 specTex = texture(material.specular, v_TexCoord).rgb;

    vec3 result = CalDirLight(dirLight, normal, viewDir, diffTex, specTex);
        
    for (int i = 0; i < numPointLights; i++)
    {
        result += CalPointLight(pointLights[i], normal, viewDir, diffTex, specTex);
    }
    
    result += CalSpotLight(spotLight, normal, viewDir, diffTex, specTex);

    color = vec4(result, 1.0);
}