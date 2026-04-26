#include "BulletHell.h"
#include <BulletHell/BHPlayer.h>
#include <BulletHell/Boss.h>
#include "AssetsModule.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "Texture.h"
#include "WindowModule.h"
#include "BulletHell/BHHealth.h"

BulletHell::BulletHellScene::BulletHellScene() : Scene("BulletHell")
{
    WindowModule* window = Engine::GetInstance()->GetModuleManager()->GetModule<WindowModule>();
    window->SetSize({ 1280u, 960u });
    window->SetTitle("Bullet Hell");

    AssetsModule* assets = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();

    // Joueur
    Texture* playerTex = assets->LoadAsset<Texture>("BHPlayer.png");
    GameObject* player = CreateGameObject("Player");
    player->SetPosition({ 640.f, 800.f });
    player->CreateComponent<SpriteRenderer>(playerTex);
    player->CreateComponent<BulletHell::BHPlayer>();
    SquareCollider* pc = player->CreateComponent<SquareCollider>();
    pc->SetWidth(32.f);
    pc->SetHeight(32.f);
    player->CreateComponent<Health>(100.f);

    // Boss
    Texture* bossTex = assets->LoadAsset<Texture>("BHBoss.png");
    GameObject* boss = CreateGameObject("Boss");
    boss->SetPosition({ 640.f, 200.f });
    boss->CreateComponent<SpriteRenderer>(bossTex);
    boss->CreateComponent<BulletHell::Boss>();
    boss->CreateComponent<Health>(500.f);
}