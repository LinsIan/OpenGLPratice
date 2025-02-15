#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);// �ĤG�ӰѼƬOshader���ƶq
    glCompileShader(id);

	int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* errMsg = (char*)alloca(length * sizeof(char)); // alloca�bstatck�W�ӽФ��s�A���ݭn�ۤv�R��
        glGetShaderInfoLog(id, length, &length, errMsg);
        std::cout << "Fiaild to compile" << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << "shader!" << std::endl << errMsg << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    // �s������i�H��shader��l�X�R��
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
};

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error!" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    float position[6] = 
    {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), position, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

    // shader�����G�ŧiposition�A�z�Lid0���opostion Attrib�A�ëŧi��vector4�A��������Ʒ|�۰ʸ�
    std::string vertexSahder = 
        R"(
        #version 330 core
        
        layout(location = 0) in vec4 position; //in�N���J�ܼơA�|��ӳ��Iid=0��attrib���

        void main()
        {
            gl_Position = position; // gl_Position�O���ت��A�N���I����m
        }
        )";

    std::string fragmentSahder =
        R"(
        #version 330 core
        
        //�w�q�@�ӿ�X�ܶq�A�M��j�w��framebuffer���Ĥ@���C��w�İϡ]�]�N�O�̲קe�{�b�ù��W���D�n�C��buffer)
        layout(location = 0) out vec4 color;

        void main()
        {
            color = vec4(1.0, 0.0, 0.0, 1.0);
        }
        )";

    unsigned int shader = CreateShader(vertexSahder, fragmentSahder);
    glUseProgram(shader);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);
    
    glfwTerminate();
    return 0;
}