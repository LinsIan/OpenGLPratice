#pragma once
#include "Sample.h"
#include "Renderer.h"
#include "Material.h"
#include "Rectangle.h"

#include <memory>

namespace Sample
{
    class SampleTextureMix : public Sample
    {
    private: 
        std::unique_ptr<Renderer> renderer;
        std::unique_ptr<Material> material;
        std::unique_ptr<Model::Rectangle> rectangle;

        float mixValue;
        float filteringMode;
		float wrappingMode;
    public:
        SampleTextureMix();
        ~SampleTextureMix();
		void OnRender() override;
        void OnImguiRender() override;
    };
}

