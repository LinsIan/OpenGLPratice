#pragma once
#include <glad/glad.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#ifdef _MSC_VER
    #define ASSERT(x) if(x) __debugbreak();
#elif defined(__GNUC__) || defined(__clang__)
    #include <signal.h>
    #define ASSERT(x) if(x) raise(SIGTRAP);
#else
    #error "Unsupported compiler"
#endif

#define GLCall(x) GLClearError();\
                  x;\
                  ASSERT(GLCheckError(#x, __FILE__, __LINE__));\

void GLClearError();
bool GLCheckError(const char* funcName, const char* file, int line);

class Renderer
{
public:
    static void Clear();
    static void Draw(const VertexArray& va, const Shader& shader, const unsigned int indexCount);
    static void SetPolygonMode(GLenum mode);
};

