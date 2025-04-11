#pragma once

#include "Sample.h"
#include "Camera.h"
#include "GameObject.h"

#include <memory>

namespace Sample
{
    class SampleTexture2D : public Sample
    {
    private:
        std::unique_ptr<GameObject> rectangle;
        std::unique_ptr<Camera> camera;
        
    public:
        SampleTexture2D();
        ~SampleTexture2D();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImguiRender() override;
    };
    
} // namespace Sample
