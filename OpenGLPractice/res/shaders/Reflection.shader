#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 u_MVP;

out vec3 v_Normal;
out vec3 v_FragPos;

void main()
{
    gl_Position = u_MVP * position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Normal;
in vec3 v_FragPos;

uniform vec3 u_ViewPos;
uniform samplerCube u_Cubemap;

void main()
{
    vec3 I = normalize(v_FragPos - u_ViewPos);
    vec3 R = reflect(I, normalize(v_Normal));
    color = vec4(texture(u_Cubemap, R).rgb, 1.0);
}
