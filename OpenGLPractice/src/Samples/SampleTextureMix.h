#pragma once
#include "Sample.h"
#include "GameObject.h"

#include <memory>

namespace Sample
{
    class SampleTextureMix : public Sample
    {
    private: 
        std::unique_ptr<GameObject> rectangle;

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

