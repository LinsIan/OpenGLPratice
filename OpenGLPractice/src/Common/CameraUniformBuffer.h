#pragma once
#include <memory>
#include "UniformBuffer.h"

class CameraUniformBuffer
{
private:
    std::unique_ptr<UniformBuffer> uniformBuffer;

public:
    static const unsigned int BINDING_POINT = 0;
    
    CameraUniformBuffer()
    {
        uniformBuffer = std::make_unique<UniformBuffer>(sizeof(glm::mat4) * 2, BINDING_POINT);
    }
    
    ~CameraUniformBuffer()
    {
    }

    void UpdateProjectionMatrix(const glm::mat4& projectionMatrix)
    {
        uniformBuffer->SetData(0, sizeof(glm::mat4), &projectionMatrix);
    }

    void UpdateViewMatrix(const glm::mat4& viewMatrix)
    {
        uniformBuffer->SetData(sizeof(glm::mat4), sizeof(glm::mat4), &viewMatrix);
    }


};

