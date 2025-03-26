#pragma once

#include "Sample.h"
#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <memory>

namespace Sample
{
	class SampleRectangle : public Sample
	{
	private:
		std::unique_ptr<Renderer> renderer;
		std::unique_ptr<Shader> shader;
		std::unique_ptr<VertexArray> vertexArray;
		std::unique_ptr<VertexBuffer> vertexBuffer;
		std::unique_ptr<IndexBuffer> indexBuffer;

		float r = 0;
        float increment = 0.05f;
		
	public:
		SampleRectangle();
		~SampleRectangle();
		
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
	};

	
	
} // namespace Sample
