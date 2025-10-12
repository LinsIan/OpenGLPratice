#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

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

uniform Material material;
uniform SpotLight spotLight;
uniform vec3 u_ViewPos;
uniform mat3 u_NormalMatrix;

vec3 CalSpotLight(vec3 normal, vec3 lightDir, vec3 viewDir)
{
	float theta = dot(lightDir, normalize(-spotLight.direction));
	float epsilon   = spotLight.cutOff - spotLight.outerCutOff;
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
	vec3 lightDir = normalize(spotLight.position - v_FragPos);
	vec3 viewDir = normalize(u_ViewPos - v_FragPos);

	color = vec4(CalSpotLight(normal, lightDir, viewDir), 1.0);
}