#pragma once

#include "Core/Scene.h"

namespace TETRIS
{
    class TetrisScene final : public Scene
    {
    public:
        TetrisScene();

        float minSize = 100.f;
        float maxSize = 300.f;
    };
}

