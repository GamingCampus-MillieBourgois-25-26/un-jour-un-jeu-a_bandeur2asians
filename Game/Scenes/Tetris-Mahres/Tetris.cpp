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



TETRIS::TetrisScene::TetrisScene() : Scene("Tetris")
{
    AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
    Texture* playerTexture = assets_module->LoadAsset<Texture>("Rectangle.png");

    GameObject* const& playerObject = CreateGameObject("Player");
    playerObject->CreateComponent<SpriteRenderer>(playerTexture);
    playerObject->CreateComponent<TETRIS::Player>();

}
