// shader�����G�ŧiposition�A�z�Lid0���opostion Attrib�A�ëŧi��vector4�A��������Ʒ|�۰ʸ�

// �۩w�q���y�k�A�Ψ�Ū�ɮɽT�{�O����shader
#shader vertex
#version 330 core

layout(location = 0) in vec4 position; //in�N����J�ܼơA�|��ӳ��Iid=0��attrib���
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

void main()
{
    gl_Position = position; // gl_Position�O���ت��A�N�����I����m
    v_TexCoord = texCoord;
}

#shader fragment
#version 330 core

//�w�q�@�ӿ�X�ܶq�A�M��j�w��framebuffer���Ĥ@���C��w�İϡ]�]�N�O�̲קe�{�b�ù��W���D�n�C��buffer)
layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoord);
    color = texColor;
}
