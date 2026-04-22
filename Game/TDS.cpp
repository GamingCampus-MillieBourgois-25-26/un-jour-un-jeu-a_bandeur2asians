#include "TDS.h"
#include "A_TDS/Player.h"

#include <chrono>
#include <cstdint>
#include <random>

#include "AssetsModule.h"
#include "RectangleShapeRenderer.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "Texture.h"
#include "WindowModule.h"


TDS::TopDownShooter::TopDownShooter(): Scene("TopDownShooter")
{
    AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
    Texture* playerTexture = assets_module->LoadAsset<Texture>("Player.png");

    GameObject* const& playerObject = CreateGameObject("Player");
    playerObject->CreateComponent<SpriteRenderer>(playerTexture);
    playerObject->CreateComponent<TDS::Player>();
}


