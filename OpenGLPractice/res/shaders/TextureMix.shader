#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

uniform mat4 u_MVP;

out vec2 v_TexCoord;

void main()
{
    gl_Position = u_MVP * position;
    v_TexCoord = texCoord;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_TextureA;
uniform sampler2D u_TextureB;
uniform float u_Degree;

void main()
{
    vec2 coordA = vec2(1 - v_TexCoord.x, v_TexCoord.y);
    color = mix(texture(u_TextureA, coordA), texture(u_TextureB, v_TexCoord), u_Degree);
}
