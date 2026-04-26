#pragma once
#include "Core/Component.h"
#include "SquareCollider.h"
#include <string>

namespace TDS
{
    class Map : public Component
    {
    public:
        void Awake() override
        {
            static const int GRID[15][20] =
            {
                { 0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0 },
                { 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1 },
                { 0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0 },
                { 0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0 },
                { 0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
                { 0,0,1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0 },
                { 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
                { 0,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0 },
                { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0 },
                { 0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,0 },
                { 0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0 },
                { 0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0 },
                { 0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0 },
                { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0 },
                { 0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0 },
            };

            const float tileSize = 64.f;
            int index = 0;
            for (int row = 0; row < 15; row++)
            {
                for (int col = 0; col < 20; col++)
                {
                    if (GRID[row][col] == 1)
                    {
                        GameObject* wall = GetOwner()->GetScene()->CreateGameObject("Wall_" + std::to_string(index++));
                        wall->SetPosition({
                            col * tileSize + tileSize * 0.5f,
                            row * tileSize + tileSize * 0.5f
                            });
                        SquareCollider* sc = wall->CreateComponent<SquareCollider>();
                        sc->SetWidth(tileSize * 0.5f);
                        sc->SetHeight(tileSize * 0.5f);
                    }
                }
            }
        }
    };
}
