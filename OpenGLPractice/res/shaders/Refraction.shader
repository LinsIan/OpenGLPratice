#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;

uniform mat4 u_MVP;
uniform mat4 u_Model;

out vec3 v_Normal;
out vec3 v_FragPos;

void main()
{
    v_Normal = normal;
    v_FragPos = vec3(u_Model * position);
    gl_Position = u_MVP * position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Normal;
in vec3 v_FragPos;

uniform vec3 u_ViewPos;
uniform samplerCube u_Cubemap;
uniform mat3 u_NormalMatrix;
float ratio = 1.00 / 1.52;

void main()
{
    vec3 normal = normalize(u_NormalMatrix * v_Normal);
    vec3 I = normalize(v_FragPos - u_ViewPos);
    vec3 R = refract(I, normal, ratio);
    color = vec4(texture(u_Cubemap, R).rgb, 1.0);
}
