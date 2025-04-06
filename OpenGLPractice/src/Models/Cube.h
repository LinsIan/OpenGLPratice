#pragma once

#include "Model.h"

namespace Model
{
	class Cube : public Model
	{
	private:
		
	public:
		Cube(float length, float width, float height, float coordX, float coordY) : Model()
		{
			float position[] =
			{
				-width / 2, -height / 2,  length / 2,  0.0f, 0.0f, // 0
				 width / 2, -height / 2,  length / 2,  1.0f, 0.0f, // 1
				 width / 2,  height / 2,  length / 2,  1.0f, 1.0f, // 2
				-width / 2,  height / 2,  length / 2,  0.0f, 1.0f, // 3

				-width / 2, -height / 2, -length / 2,  1.0f, 0.0f, // 4
				 width / 2, -height / 2, -length / 2,  0.0f, 0.0f, // 5
				 width / 2,  height / 2, -length / 2,  0.0f, 1.0f, // 6
				-width / 2,  height / 2, -length / 2,  1.0f, 1.0f, // 7

				-width / 2, -height / 2, -length / 2,  0.0f, 0.0f, // 8
				-width / 2, -height / 2,  length / 2,  1.0f, 0.0f, // 9
				-width / 2,  height / 2,  length / 2,  1.0f, 1.0f, // 10
				-width / 2,  height / 2, -length / 2,  0.0f, 1.0f, // 11

				 width / 2, -height / 2, -length / 2,  1.0f, 0.0f, // 12
				 width / 2, -height / 2,  length / 2,  0.0f, 0.0f, // 13
				 width / 2,  height / 2,  length / 2,  0.0f, 1.0f, // 14
				 width / 2,  height / 2, -length / 2,  1.0f, 1.0f, // 15

				 -width / 2, -height / 2, -length / 2,  0.0f, 1.0f, // 16
				  width / 2, -height / 2, -length / 2,  1.0f, 1.0f, // 17
				  width / 2, -height / 2,  length / 2,  1.0f, 0.0f, // 18
				 -width / 2, -height / 2,  length / 2,  0.0f, 0.0f, // 19

				 -width / 2,  height / 2, -length / 2,  0.0f, 0.0f, // 20
				  width / 2,  height / 2, -length / 2,  1.0f, 0.0f, // 21
				  width / 2,  height / 2,  length / 2,  1.0f, 1.0f, // 22
				 -width / 2,  height / 2,  length / 2,  0.0f, 1.0f  // 23
			};

			unsigned int indices[] =
			{
				0, 1, 2,
				2, 3, 0,

				4, 5, 6,
				6, 7, 4,

				8, 9, 10,
				10, 11, 8,

				12, 13, 14,
				14, 15, 12,

				16, 17, 18,
				18, 19, 16,

				20, 21, 22,
				22, 23, 20
			};

			vertexArray = std::make_unique<VertexArray>();
			vertexBuffer = std::make_unique<VertexBuffer>(position, 24 * 5 * sizeof(float));
			VertexBufferLayout layout;
			layout.Push<float>(3); // position
			layout.Push<float>(2); // texture coordinate
			vertexArray->AddBuffer(*vertexBuffer, layout);
			indexBuffer = std::make_unique<IndexBuffer>(indices, 36);

			vertexArray->Unbind();
			vertexBuffer->Unbind();
			indexBuffer->Unbind();
		};

		~Cube(){}
	};
}