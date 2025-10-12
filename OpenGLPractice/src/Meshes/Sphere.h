#pragma once
#include "Mesh.h"
#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"

namespace Mesh
{
    class Sphere : public Mesh
    {
    public:
        Sphere(float radius, unsigned int stacks, unsigned int slices) : Mesh()
        {
            std::vector<float> positions;
            std::vector<unsigned int> indices;

            for (unsigned int i = 0; i <= stacks; ++i)
            {

                auto pi = glm::pi<float>();
                float theta = i * pi / stacks; // �n�ר�

                for (unsigned int j = 0; j <= slices; ++j)
                {
                    float phi = j * 2 * pi / slices; // �g�ר�

                    // �p�⳻�I��m
                    float x = radius * sin(theta) * cos(phi);
                    float y = radius * cos(theta);
                    float z = radius * sin(theta) * sin(phi);

                    // �p�⯾�z�y��
                    float u = (float)j / slices;
                    float v = (float)i / stacks;

                    // �K�[���I�ݩ�
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

                    // �K�[����
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
            indexBuffer = std::make_unique<IndexBuffer>(indices.data(), indices.size());
            vertexArray->AddBuffer(*vertexBuffer, layout, *indexBuffer);

            vertexArray->Unbind();
            vertexBuffer->Unbind();
            indexBuffer->Unbind();
        }

        ~Sphere() {}
    };
} // namespace Model