#pragma once

#include "Sample.h"
#include "Renderer.h"
#include "Material.h"
#include "Rectangle.h"

#include <memory>

namespace Sample
{
	class SampleRectangle : public Sample
	{
	private:
		std::unique_ptr<Renderer> renderer;
		std::unique_ptr<Material> material;
		std::unique_ptr<Model::Rectangle> rectangle;

		float r = 0;
        float increment = 0.05f;
		
	public:
		SampleRectangle();
		~SampleRectangle();
		
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
	};

	
	
} // namespace Sample
