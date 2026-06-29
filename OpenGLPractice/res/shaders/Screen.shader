#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 2) in vec2 texCoord;

uniform mat4 u_Model;

out vec2 v_TexCoord;

void main()
{
    gl_Position = u_Model * position;
    v_TexCoord = texCoord;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
    // normal
    vec4 texColor = texture(u_Texture, v_TexCoord);
    color = texColor;
}
