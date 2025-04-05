#pragma once
#include "Sample.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "Rectangle.h"

#include <memory>

namespace Sample
{
    class SampleTextureMix : public Sample
    {
    private: 
        std::unique_ptr<Renderer> renderer;
        std::unique_ptr<Shader> shader;
        std::unique_ptr<Texture> textureSmile;
        std::unique_ptr<Texture> textureBox;
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

