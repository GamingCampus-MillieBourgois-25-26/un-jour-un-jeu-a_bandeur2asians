#pragma once

#include "Core/Scene.h"

namespace DTS
{
    class DTSScene final : public Scene
    {
    public:
        DTSScene();

        void CreateRandomTile();

        float minSize = 100.f;
        float maxSize = 300.f;
    };
}

