#pragma once
#include "Model.h"
#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"

namespace Model
{
    class Sphere : public Model
    {
    public:
        Sphere(float radius, unsigned int stacks, unsigned int slices) : Model()
        {
            std::vector<float> positions;
            std::vector<unsigned int> indices;

            for (unsigned int i = 0; i <= stacks; ++i)
            {

                auto pi = glm::pi<float>();
                float theta = i * pi / stacks; // 緯度角

                for (unsigned int j = 0; j <= slices; ++j)
                {
                    float phi = j * 2 * pi / slices; // 經度角

                    // 計算頂點位置
                    float x = radius * sin(theta) * cos(phi);
                    float y = radius * cos(theta);
                    float z = radius * sin(theta) * sin(phi);

                    // 計算紋理座標
                    float u = (float)j / slices;
                    float v = (float)i / stacks;

                    // 添加頂點屬性
                    positions.push_back(x);
                    positions.push_back(y);
                    positions.push_back(z);
                    positions.push_back(u);
                    positions.push_back(v);
                }
            }

            for (unsigned int i = 0; i < stacks; ++i)
            {
                for (unsigned int j = 0; j < slices; ++j)
                {
                    unsigned int first = i * (slices + 1) + j;
                    unsigned int second = first + slices + 1;

                    // 添加索引
                    indices.push_back(first);
                    indices.push_back(second);
                    indices.push_back(first + 1);

                    indices.push_back(second);
                    indices.push_back(second + 1);
                    indices.push_back(first + 1);
                }
            }

            vertexArray = std::make_unique<VertexArray>();
            vertexBuffer = std::make_unique<VertexBuffer>(positions.data(), positions.size() * sizeof(float));
            VertexBufferLayout layout;
            layout.Push<float>(3); // position
            layout.Push<float>(2); // texture coordinate
            vertexArray->AddBuffer(*vertexBuffer, layout);
            indexBuffer = std::make_unique<IndexBuffer>(indices.data(), indices.size());

            vertexArray->Unbind();
            vertexBuffer->Unbind();
            indexBuffer->Unbind();
        }

        ~Sphere() {}
    };
} // namespace Model