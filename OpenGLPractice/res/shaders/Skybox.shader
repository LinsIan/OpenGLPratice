#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(std140) uniform Matrices
{
    mat4 u_Projection;
    mat4 u_View;
};

uniform mat4 u_Model;

out vec3 v_TexCoord;

void main()
{
    mat4 noTranslationView = mat4(mat3(u_View));
    vec4 pos = u_Projection * noTranslationView * u_Model * position;
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
