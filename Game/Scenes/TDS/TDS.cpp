#include "TDS.h"
#include <chrono>
#include <cstdint>
#include <random>
#include "AssetsModule.h"
#include "RectangleShapeRenderer.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "Texture.h"
#include "WindowModule.h"
#include <TDS/Player.h>
#include <TDS/Background.h>

TDS::TopDownShooter::TopDownShooter() : Scene("TopDownShooter")
{
    AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();

    // Map visuelle
    Texture* mapTexture = assets_module->LoadAsset<Texture>("map.png");
    GameObject* bg = CreateGameObject("Background");
    bg->SetPosition({ 0.f, 0.f });
    bg->CreateComponent<SpriteRenderer>(mapTexture);
    bg->CreateComponent<TDS::Map>();

    // Player
    Texture* playerTexture = assets_module->LoadAsset<Texture>("Player.png");
    GameObject* playerObject = CreateGameObject("Player");
    playerObject->SetPosition({ 150.f, 500.f });
    playerObject->CreateComponent<SpriteRenderer>(playerTexture);
    playerObject->CreateComponent<TDS::Player>();
    SquareCollider* pc = playerObject->CreateComponent<SquareCollider>();
    pc->SetWidth(64.f);
    pc->SetHeight(64.f);
}