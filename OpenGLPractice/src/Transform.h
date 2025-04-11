#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>

class Transform
{
private:
    std::unique_ptr<glm::vec3> translation;
    std::unique_ptr<glm::vec3> scale;
    std::unique_ptr<glm::vec3> radians;

    glm::mat4 matrix;

    void UpdateModelMatrix()
    {
        matrix = glm::translate(glm::mat4(1.0f), *translation) *
            glm::rotate(glm::mat4(1.0f), glm::radians(radians->x), glm::vec3(1, 0, 0)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(radians->y), glm::vec3(0, 1, 0)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(radians->z), glm::vec3(0, 0, 1)) *
            glm::scale(glm::mat4(1.0f), *scale);
    }
public:
    Transform()
    {
        translation = std::make_unique<glm::vec3>(0.0f, 0.0f, 0.0f);
        scale = std::make_unique<glm::vec3>(1.0f, 1.0f, 1.0f);
        radians = std::make_unique<glm::vec3>(0.0f, 0.0f, 0.0f);
    }

	~Transform() {}

    const glm::mat4 GetMatrix()
    {
        UpdateModelMatrix();
        return matrix;
    }

    void SetTranslation(float x, float y, float z)
    {
        translation->x = x;
        translation->y = y;
        translation->z = z;
    }

    void SetScale(float x, float y, float z)
    {
        scale->x = x;
        scale->y = y;
        scale->z = z;
    }

    void SetRotation(float x, float y, float z)
    {
        radians->x = x;
        radians->y = y;
        radians->z = z;
    }

    glm::vec3& GetTranslation() const { return *translation; }
    glm::vec3& GetScale() const { return *scale; }
    glm::vec3& GetRotation() const { return *radians; }

};