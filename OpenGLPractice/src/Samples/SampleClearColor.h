#pragma once

#include "Sample.h"

namespace Sample
{
    class SampleClearColor : public Sample
    {
    private:
        float clearColor[4];
    public:
        SampleClearColor();
        ~SampleClearColor();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImguiRender() override; 
    };
    
} // namespace Sample
