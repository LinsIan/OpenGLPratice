// shader�����G�ŧiposition�A�z�Lid0���opostion Attrib�A�ëŧi��vector4�A��������Ʒ|�۰ʸ�

// �۩w�q���y�k�A�Ψ�Ū�ɮɽT�{�O����shader
#shader vertex
#version 330 core
        
layout(location = 0) in vec4 position; //in�N���J�ܼơA�|��ӳ��Iid=0��attrib���

void main()
{
    gl_Position = position; // gl_Position�O���ت��A�N���I����m
}

#shader fragment
#version 330 core
        
//�w�q�@�ӿ�X�ܶq�A�M��j�w��framebuffer���Ĥ@���C��w�İϡ]�]�N�O�̲קe�{�b�ù��W���D�n�C��buffer)
layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main()
{
    color = u_Color;
}
