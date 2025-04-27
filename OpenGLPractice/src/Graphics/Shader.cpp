#include "Shader.h"
#include "Renderer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


Shader::Shader(const std::string& filepath)
    : filepath(filepath), rendererID(0)
{
    ShaderSource source = ParseShader(filepath);
    rendererID = CreateShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(rendererID));
}

ShaderSource Shader::ParseShader(const std::string& filepath)
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

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

	int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        auto errMsg = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, errMsg);
        std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << "shader!" << std::endl << errMsg << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
};


void Shader::Bind() const
{
    GLCall(glUseProgram(rendererID));
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    int location = GetUniformLocation(name);
    GLCall(glUniform1i(location, value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
    int location = GetUniformLocation(name);
    GLCall(glUniform1f(location, value));
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
    int location = GetUniformLocation(name);
    GLCall(glUniform3f(location, v0, v1, v2));
}

void Shader::SetUniform3f(const std::string& name, glm::vec3 vector)
{
	int location = GetUniformLocation(name);
	GLCall(glUniform3f(location, vector.x, vector.y, vector.z));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    int location = GetUniformLocation(name);
    GLCall(glUniform4f(location, v0, v1, v2, v3));
}

void Shader::SetUniformMat3f(const std::string& name, const glm::mat3& matrix)
{
    int location = GetUniformLocation(name);
    glUniformMatrix3fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    int location = GetUniformLocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (locationCache.find(name) != locationCache.end())
    {
        return locationCache[name];
    }

    int location = glGetUniformLocation(rendererID, name.c_str());
    
    if (location == -1)
    {
        std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;
    }

    locationCache[name] = location;
    return location;
}
