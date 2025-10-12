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
            vertices.clear();
            vertices.reserve((stacks + 1) * (slices + 1));

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
                    float u = static_cast<float>(j) / slices;
                    float v = static_cast<float>(i) / stacks;

                    glm::vec3 pos(x, y, z);
                    glm::vec3 nrm = glm::normalize(pos);

                    vertices.push_back(Vertex{ pos, nrm, glm::vec2(u, v) });
                }
            }

            indices.clear();
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

            SetupMesh();
        }

        ~Sphere() {}
    };
} // namespace Model