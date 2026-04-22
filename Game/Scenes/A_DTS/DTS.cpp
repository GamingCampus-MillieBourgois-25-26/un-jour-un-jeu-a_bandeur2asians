#include "DTS.h"

#include <chrono>
#include <cstdint>
#include <random>

#include "AssetsModule.h"
#include "RectangleShapeRenderer.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "Texture.h"
#include "WindowModule.h"
#include "A_DTS/PlayerDTS.h"

DTS::DTSScene::DTSScene(): Scene("DTS")
{
    AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
    Texture* playerTexture = assets_module->LoadAsset<Texture>("maincharacter.png");

    GameObject* const& playerObject = CreateGameObject("Player");
    playerObject->CreateComponent<SpriteRenderer>(playerTexture);
    playerObject->CreateComponent<DTS::Player>();

}