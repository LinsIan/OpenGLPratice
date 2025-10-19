#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

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

uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform int u_DepthTestEnabled;
uniform int u_LinearizedDepth;

float near = 0.1; 
float far  = 10.0;

void main()
{
    if (u_LinearizedDepth == 1)
    {
        float z = gl_FragCoord.z * 2.0 - 1.0;
        float linearDepth = (2.0 * near * far) / (far + near - z * (far - near));  
        color = vec4(vec3(linearDepth / far), 1.0);
        return;
    }

    if (u_DepthTestEnabled == 1)
    {
        color = vec4(vec3(gl_FragCoord.z), 1.0);
        return;
    }
    
    vec4 texColor = texture(u_Texture, v_TexCoord);
    color = texColor;
    
}
