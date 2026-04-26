#include "BulletHell-M.h"

#include <chrono>
#include <cstdint>
#include <random>
#include <iostream>
#include <cmath>
#include <algorithm>

#include "AssetsModule.h"
#include "RectangleShapeRenderer.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "Texture.h"
#include "WindowModule.h"

#include "Bullet-L/OppsTank.h"
#include "Bullet-L/PlayerBulletHell.h"

sf::Texture textureTank1;
sf::Texture textureTank2;
sf::Texture textureTank3;
sf::Texture textureTank4;
sf::Texture textureTank5;

bool texturesLoaded = false;

HELL::HELLScene::HELLScene() : Scene("BULLET HELL")
{
    AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
    WindowModule* window = Engine::GetInstance()->GetModuleManager()->GetModule<WindowModule>();

    Maths::Vector2u windowSize = window->GetSize();
    float centerX = windowSize.x / 2.f;
    float centerY = windowSize.y / 2.f;

    Texture* playerTexture = assets_module->LoadAsset<Texture>("TankPlayer.png");
    GameObject* const& playerObject = CreateGameObject("Player");
    playerObject->CreateComponent<SpriteRenderer>(playerTexture);
    playerObject->CreateComponent<HELL::Player>();
    playerObject->SetPosition({ centerX, centerY });
    playerObject->SetScale({ 0.5f, 0.5f });

    std::vector<std::pair<std::string, float>> enemyTypes = {
        { "TankOpp1.png", 1.f   },
        { "TankOpp2.png", 1.5f  },
        { "TankOpp3.png", 1.f  },
        { "TankOpp4.png", 2.f   },
        { "TankOpp5.png", 0.5f  }
    };

    int count = enemyTypes.size();
    float radius = 300.f; // distance du centre, ajuste selon ta fenêtre

    for (int i = 0; i < count; i++)
    {
        float angle = (2.f * 3.14159f / count) * i; // répartition uniforme
        float x = centerX + radius * std::cos(angle);
        float y = centerY + radius * std::sin(angle);

        auto& [textureName, fireRate] = enemyTypes[i];
        Texture* enemyTexture = assets_module->LoadAsset<Texture>(textureName);
        GameObject* enemy = CreateGameObject("Opp");
        enemy->CreateComponent<SpriteRenderer>(enemyTexture);
        auto* opps = enemy->CreateComponent<HELL::Opps>();
        opps->fireRate = fireRate;
        enemy->CreateComponent<HELL::Health>(100.f);
        enemy->SetPosition({ x, y });
        enemy->SetScale({ 0.5f, 0.5f });
    }
}