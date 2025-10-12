#pragma once

#include "Mesh.h"

namespace Mesh
{
    class Rectangle : public Mesh
    {
    public:
        Rectangle(float width, float height, float coordX, float coordY) : Mesh()
        {
            vertices = {
                { {-width / 2, -height / 2, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f} }, // 0
                { { width / 2, -height / 2, 0.0f}, {0.0f, 0.0f, 1.0f}, {coordX, 0.0f} }, // 1
                { { width / 2,  height / 2, 0.0f}, {0.0f, 0.0f, 1.0f}, {coordX, coordY} }, // 2
                { {-width / 2,  height / 2, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, coordY} }, // 3
            };

            indices =
            {
                0, 1, 2,
                2, 3, 0
            };

            SetupMesh();
        };

        ~Rectangle() {}
    };
} // namespace Mesh

