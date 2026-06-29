#pragma once

#include "GameObject.h"
#include <string>
#include <vector>

class Skybox : public GameObject
{
public:
    Skybox(const std::vector<std::string>& faces);
    ~Skybox() = default;

    void OnRender();
};
