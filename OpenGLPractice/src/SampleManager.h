#pragma once
#include <memory>

#include "Samples/Sample.h"

class SampleManager
{
private:
    std::unique_ptr<Sample::Sample> sample;
public:
    SampleManager();
    ~SampleManager();

    void OnUpdate();
};
