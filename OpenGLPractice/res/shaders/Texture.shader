#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

layout(std140) uniform Matrices
{
    mat4 u_Projection;
    mat4 u_View;
};
uniform mat4 u_Model;

out vec2 v_TexCoord;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * position;
    v_TexCoord = texCoord;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;
const float offset = 1.0 / 300.0;  

void main()
{
    // normal
    vec4 texColor = texture(u_Texture, v_TexCoord);
    color = texColor;

    // Inversion
    // vec4 texColor = vec4(1 - texture(u_Texture, v_TexCoord).rgb, 1.0);
    // color = texColor;
    
    // Grayscale
    // float average = 0.2126 * texColor.r + 0.7152 * texColor.g + 0.0722 * texColor.b;
    // color = vec4(average, average, average, 1.0);

    // Kernel
    // vec2 offsets[9] = vec2[](
    //     vec2(-offset,  offset), // top-left
    //     vec2( 0.0f,    offset), // top
    //     vec2( offset,  offset), // top-right
    //     vec2(-offset,  0.0f),   // left
    //     vec2( 0.0f,    0.0f),   // center
    //     vec2( offset,  0.0f),   // right
    //     vec2(-offset, -offset), // bottom-left
    //     vec2( 0.0f,   -offset), // bottom
    //     vec2( offset, -offset)  // bottom-right
    // );

    // float SharpenKernel[9] = float[](
    //     -1, -1, -1,
    //     -1,  9, -1,
    //     -1, -1, -1
    // );

    // float BlurKernel[9] = float[](
    //     1.0/16, 2.0/16, 1.0/16,
    //     2.0/16, 4.0/16, 2.0/16,
    //     1.0/16, 2.0/16, 1.0/16
    // );

    // float EdgeDetectKernel[9] = float[](
    //     1,  1, 1,
    //     1, -8, 1,
    //     1,  1, 1
    // );

    // float kernel[9] = EdgeDetectKernel; // Change this to switch between kernels

    // vec3 sampleTex[9];
    // for(int i = 0; i < 9; i++)
    // {
    //     sampleTex[i] = vec3(texture(u_Texture, v_TexCoord.st + offsets[i]));
    // }
    // vec3 col = vec3(0.0);
    // for(int i = 0; i < 9; i++)
    //     col += sampleTex[i] * kernel[i];

    // color = vec4(col, 1.0);
}
