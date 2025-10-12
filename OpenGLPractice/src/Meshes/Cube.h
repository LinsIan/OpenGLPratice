#pragma once

#include "Mesh.h"

namespace Mesh
{
	class Cube : public Mesh
	{
	public:
		Cube(float length, float width, float height) : Mesh()
		{
            float len = length / 2;
            float wid = width / 2;
            float hei = height / 2;
			
			vertices = {
				{{ -wid, -hei,  len }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }}, // 0
				{{  wid, -hei,  len }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f }}, // 1
				{{  wid,  hei,  len }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f }}, // 2
				{{ -wid,  hei,  len }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f }}, // 3

				{{ -wid, -hei, -len }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f }}, // 4
				{{  wid, -hei, -len }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f }}, // 5
				{{  wid,  hei, -len }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f }}, // 6
				{{ -wid,  hei, -len }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f }}, // 7

				{{ -wid, -hei, -len }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }}, // 8
				{{ -wid, -hei,  len }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }}, // 9
				{{ -wid,  hei,  len }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }}, // 10
				{{ -wid,  hei, -len }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }}, // 11

				{{  wid, -hei, -len }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }}, // 12
				{{  wid, -hei,  len }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }}, // 13
				{{  wid,  hei,  len }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }}, // 14
				{{  wid,  hei, -len }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }}, // 15

				{{ -wid, -hei, -len }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f }}, // 16
				{{  wid, -hei, -len }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 1.0f }}, // 17
				{{  wid, -hei,  len }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 0.0f }}, // 18
				{{ -wid, -hei,  len }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f }}, // 19

				{{ -wid,  hei, -len }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f }}, // 20
				{{  wid,  hei, -len }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f }}, // 21
				{{  wid,  hei,  len }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f }}, // 22
				{{ -wid,  hei,  len }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f }}, // 23
			};

			indices =
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

			SetupMesh();
		};

		~Cube(){}
	};
}