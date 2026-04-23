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
#include <TDS/Enemy.h>
#include <TDS/Health.h>

TDS::TopDownShooter::TopDownShooter() : Scene("TopDownShooter")
{
    WindowModule* window = Engine::GetInstance()->GetModuleManager()->GetModule<WindowModule>();
    window->SetSize({ 1280, 960 });
    window->SetTitle("Top Down Shooter");

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


    Texture* enemyTexture = assets_module->LoadAsset<Texture>("Enemy.png");
    for (int i = 0; i < 3; i++)
    {
        GameObject* enemy = CreateGameObject("Enemy");
        enemy->SetPosition(TDS::GetRandomSpawnPos());
        enemy->CreateComponent<SpriteRenderer>(enemyTexture);
        enemy->CreateComponent<TDS::Enemy>();
        enemy->CreateComponent<TDS::Health>(100.f);
    }

    // Health du joueur
    playerObject->CreateComponent<TDS::Health>(100.f);
}