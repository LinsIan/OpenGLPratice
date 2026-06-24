#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
uniform mat4 u_MVP;

out vec3 v_TexCoord;

void main()
{
    vec4 pos = u_MVP * position;
    gl_Position = pos.xyww;

    // TexCoord is the same as position for skybox, since we are using a cube map
    v_TexCoord = position.xyz;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_TexCoord;

uniform samplerCube u_Cubemap;

void main()
{
    vec4 texColor = texture(u_Cubemap, v_TexCoord);
    color = texColor;
}
