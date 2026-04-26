#pragma once

#include "Core/Scene.h"

namespace HELL
{
    class HELLScene final : public Scene
    {
    public:
        HELLScene();


        float minSize = 100.f;
        float maxSize = 300.f;
    };
}

