#pragma once

#include "Sample.h"
#include "GameObject.h"

#include <memory>

namespace Sample
{
	class SampleRectangle : public Sample
	{
	private:
		std::unique_ptr<GameObject> rectangle;

		float r = 0;
        float increment = 0.05f;
		
	public:
		SampleRectangle();
		~SampleRectangle();
		
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
	};

	
	
} // namespace Sample
