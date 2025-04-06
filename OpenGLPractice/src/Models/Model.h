#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>



namespace Model
{
    class Model
    {
    protected:
        std::unique_ptr<VertexArray> vertexArray;
        std::unique_ptr<VertexBuffer> vertexBuffer;
        std::unique_ptr<IndexBuffer> indexBuffer;

        std::unique_ptr<glm::vec3> translation;
        std::unique_ptr<glm::vec3> scale;
        std::unique_ptr<glm::vec3> radians;

        glm::mat4 modelMatrix;

        void UpdateModelMatrix()
        {
            modelMatrix = glm::translate(glm::mat4(1.0f), *translation) *
                          glm::rotate(glm::mat4(1.0f), radians->x, glm::vec3(1, 0, 0)) *
                          glm::rotate(glm::mat4(1.0f), radians->y, glm::vec3(0, 1, 0)) *
                          glm::rotate(glm::mat4(1.0f), radians->z, glm::vec3(0, 0, 1)) *
                          glm::scale(glm::mat4(1.0f), *scale);
        }

    public:
        Model()
            : translation(std::make_unique<glm::vec3>(0.0f, 0.0f, 0.0f)),
              scale(std::make_unique<glm::vec3>(1.0f, 1.0f, 1.0f)),
              radians(std::make_unique<glm::vec3>(0.0f, 0.0f, 0.0f)),
              modelMatrix(glm::mat4(1.0f))
        {}

        virtual ~Model() {}

        const glm::mat4 GetModelMatrix()
        {
            UpdateModelMatrix();
            return modelMatrix;
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
        
        inline const VertexArray& GetVertexArray() const { return *vertexArray; }
        inline const IndexBuffer& GetIndexBuffer() const { return *indexBuffer; }
    };
} // namespace Model