#pragma once
#include <memory>

#include "Samples/Sample.h"
#include "GameObject.h"
#include "Camera.h"

class SampleManager
{
private:
    unsigned int framebuffer;
    unsigned int texColorBuffer;
    std::unique_ptr<Sample::Sample> sample;
    std::unique_ptr<GameObject> screen;
public:
    SampleManager();
    ~SampleManager();

    void OnUpdate();
};
