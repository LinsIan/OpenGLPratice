#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define ASSERT(x) if(x) __debugbreak();

#define GLCall(x) GLClearError();\
                  x;\
                  ASSERT(GLCheckError(#x, __FILE__, __LINE__));\

static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR) {}
}

static bool GLCheckError(const char* funcName, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "): " << funcName << " "
        << file << ":" << line << std::endl;
        return true;
    }

    return false;
}


struct ShaderSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

static ShaderSource ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

    std::string str;
	ShaderType type = ShaderType::NONE;
	std::stringstream ss[2];

    while (getline(stream, str))
    {
		if (str.find("#shader") != std::string::npos)
        {
			if (str.find("vertex") != std::string::npos)
            {
				type = ShaderType::VERTEX;
			}
            else if (str.find("fragment") != std::string::npos)
            {
		        type = ShaderType::FRAGMENT;
			}
		}
        else if (type != ShaderType::NONE)
        {
            ss[(int)type] << str << "\n";
        }
    }

	return ShaderSource{ ss[0].str(), ss[1].str() };
};

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);// 第二個參數是shader的數量
    glCompileShader(id);

	int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* errMsg = (char*)alloca(length * sizeof(char)); // alloca在statck上申請內存，不需要自己刪除
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

    // 連結完後可以把shader原始碼刪除
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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // 設定畫面更新的頻率，1為螢幕刷新一次就更新一次
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error!" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    float position[] = 
    {
        -0.5f, -0.5f, // 0
         0.5f, -0.5f, // 1
         0.5f,  0.5f, // 2
        -0.5f,  0.5f, // 3
    };

    //一定要unsinged，另外想更省內存可以用char或是short
    unsigned int indeces[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int buffer;
    glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), position, GL_STATIC_DRAW);

    // 設定頂點屬性的時候，會把當前的vertex buffer資料存到vao當中
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    unsigned int indexBuffer;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indeces, GL_STATIC_DRAW);

    ShaderSource source = ParseShader("res/shaders/Basic.shader");

    unsigned int shader = CreateShader(source.vertexSource, source.fragmentSource);
    GLCall(glUseProgram(shader));

    int location = glGetUniformLocation(shader, "u_Color");
    ASSERT(location == -1);

    GLCall(glBindVertexArray(0));
    GLCall(glUseProgram(0));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    float r = 0;
    float increment = 0.05f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        GLCall(glUseProgram(shader));
        GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));

        GLCall(glBindVertexArray(vao)); //前面資料已經存進vao了，所以這邊綁定vao就好
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer));
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        if (r >= 1) increment = -0.05f;
        else if (r <= 0) increment = 0.05f;

        r += increment;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);
    
    glfwTerminate();
    return 0;
}