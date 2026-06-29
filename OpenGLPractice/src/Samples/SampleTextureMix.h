#pragma once
#include "Sample.h"
#include "GameObject.h"
#include "CameraUniformBuffer.h"

#include <memory>

namespace Sample
{
    class SampleTextureMix : public Sample
    {
    private: 
        std::unique_ptr<GameObject> rectangle;
        std::unique_ptr<CameraUniformBuffer> cameraUBO;

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

