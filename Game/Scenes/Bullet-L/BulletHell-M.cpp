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

void loadTextures()
{
    if (!texturesLoaded)
    {
        if (!textureTank1.loadFromFile("Assets/Ennemis/Opps1.png"))
            std::cout << "ERREUR: Impossible de charger Opps1.png" << std::endl;

        if (!textureTank2.loadFromFile("Assets/Ennemis/Opps2.png"))
            std::cout << "ERREUR: Impossible de charger Opps2.png" << std::endl;

        if (!textureTank3.loadFromFile("Assets/Ennemis/Opps3.png"))
            std::cout << "ERREUR: Impossible de charger Opps3.png" << std::endl;

        if (!textureTank4.loadFromFile("Assets/Ennemis/BOSS.png"))
            std::cout << "ERREUR: Impossible de charger BOSS.png" << std::endl;

        texturesLoaded = true;
    }
}

HELL::HELLScene::HELLScene() : Scene("BULLET HELL")
{
    AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();

    Texture* playerTexture = assets_module->LoadAsset<Texture>("TankPlayer.png");
    GameObject* const& playerObject = CreateGameObject("Player");
    playerObject->CreateComponent<SpriteRenderer>(playerTexture);
    playerObject->CreateComponent<HELL::Player>();


    
}