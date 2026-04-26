#include "Tetris.h"

#include <chrono>
#include <cstdint>
#include <random>

#include "AssetsModule.h"
#include "RectangleShapeRenderer.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "Texture.h"
#include "WindowModule.h"
#include "Tetris-Mahres/PlayerTetris.h"

static const int COLS = 10;

TETRIS::TetrisScene::TetrisScene() : Scene("Tetris")
{
    SpawnPiece();
}

void TETRIS::TetrisScene::SpawnPiece()
{
    const std::vector<std::string> textureNames = {
        "HalfSquare.png",
        "Rectangle.png",
        "Square.png",
        "ZLeft.png",
        "ZRight.png",
        "LRight.png",
        "LLeft.png"
    };

    std::mt19937 rng(static_cast<uint32_t>(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(0, (int)textureNames.size() - 1);

    AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
    Texture* playerTexture = assets_module->LoadAsset<Texture>(textureNames[dist(rng)]);

    GameObject* playerObject = CreateGameObject("Player");
    playerObject->SetPosition({ (COLS / 2) * 32.f, 0.f });
    playerObject->CreateComponent<SpriteRenderer>(playerTexture);
    playerObject->CreateComponent<TETRIS::Player>();
}
