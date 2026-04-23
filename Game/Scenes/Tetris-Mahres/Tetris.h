#pragma once

#include "Core/Scene.h"

namespace TETRIS
{
    class TetrisScene final : public Scene
    {
    public:
        TetrisScene();


    private:
		void SpawnPiece();

    };
}

