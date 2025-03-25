#pragma once

namespace Sample
{
    class Sample
    {
    public:
        Sample() {}
        virtual ~Sample(){}
    
        virtual void OnUpdate(float deltaTime) {}
        virtual void OnRender() {}
        virtual void OnImguiRender() {}
    };
} // namespace Sample



