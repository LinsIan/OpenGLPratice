#pragma once
#include <string>
#include <unordered_map>

struct ShaderSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader
{
private:
    unsigned int rendererID;
    std::string filepath;
    std::unordered_map<std::string, int> locationCache;

public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;
    void SetUniform1i(const std::string& name, int value);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
    ShaderSource ParseShader(const std::string& filepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    int GetUniformLocation(const std::string& name);
};