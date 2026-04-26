#pragma once
#include <cmath>
#include "Core/Component.h"
#include "InputModule.h"
#include "AssetsModule.h"
#include "SpriteRenderer.h"
#include "Texture.h"
#include "SquareCollider.h"
#include "Projectile.h"

namespace TDS
{
    static bool IsCollidingCentered(SquareCollider* a, SquareCollider* b)
    {
        Maths::Vector2f posA = a->GetOwner()->GetPosition();
        Maths::Vector2f posB = b->GetOwner()->GetPosition();

        float halfWA = a->GetWidth() * 0.5f;
        float halfHA = a->GetHeight() * 0.5f;
        float halfWB = b->GetWidth() * 0.5f;
        float halfHB = b->GetHeight() * 0.5f;

        return posA.x - halfWA < posB.x + halfWB &&
            posA.x + halfWA > posB.x - halfWB &&
            posA.y - halfHA < posB.y + halfHB &&
            posA.y + halfHA > posB.y - halfHB;
    }

    class Player : public Component
    {
    public:
        void Update(const float _delta_time) override
        {
            Maths::Vector2<float> position = GetOwner()->GetPosition();
            SquareCollider* playerCollider = GetOwner()->GetComponent<SquareCollider>();
            auto& objects = GetOwner()->GetScene()->GetGameObjects();

            // Mouvement X
            Maths::Vector2<float> newPosX = position;
            if (InputModule::GetKey(sf::Keyboard::Key::D))
                newPosX.x += speed * _delta_time;
            if (InputModule::GetKey(sf::Keyboard::Key::Q))
                newPosX.x -= speed * _delta_time;

            GetOwner()->SetPosition(newPosX);
            bool collideX = false;
            if (playerCollider)
            {
                for (auto& go : objects)
                {
                    if (go.get() == GetOwner()) continue;
                    SquareCollider* wallCollider = go->GetComponent<SquareCollider>();
                    if (wallCollider && IsCollidingCentered(playerCollider, wallCollider))
                    {
                        collideX = true;
                        break;
                    }
                }
            }
            if (collideX) GetOwner()->SetPosition(position);

            // Mouvement Y
            Maths::Vector2<float> posAfterX = GetOwner()->GetPosition();
            Maths::Vector2<float> newPosY = posAfterX;
            if (InputModule::GetKey(sf::Keyboard::Key::Z))
                newPosY.y -= speed * _delta_time;
            if (InputModule::GetKey(sf::Keyboard::Key::S))
                newPosY.y += speed * _delta_time;

            GetOwner()->SetPosition(newPosY);
            bool collideY = false;
            if (playerCollider)
            {
                for (auto& go : objects)
                {
                    if (go.get() == GetOwner()) continue;
                    SquareCollider* wallCollider = go->GetComponent<SquareCollider>();
                    if (wallCollider && IsCollidingCentered(playerCollider, wallCollider))
                    {
                        collideY = true;
                        break;
                    }
                }
            }
            if (collideY) GetOwner()->SetPosition(posAfterX);

            // Tir
            if (InputModule::GetKeyDown(sf::Keyboard::Key::Space))
            {
                Maths::Vector2<float> finalPos = GetOwner()->GetPosition();
                Maths::Vector2i mousePos = InputModule::GetMousePosition();
                float dx = static_cast<float>(mousePos.x) - finalPos.x;
                float dy = static_cast<float>(mousePos.y) - finalPos.y;

                AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
                Texture* projectile_texture = assets_module->LoadAsset<Texture>("TDS_Projectile.png");

                GameObject* projectile = GetOwner()->GetScene()->CreateGameObject("Projectile");
                projectile->SetPosition(finalPos);
                projectile->CreateComponent<SpriteRenderer>(projectile_texture);
                projectile->CreateComponent<Projectile>(sf::radians(std::atan2(dy, dx)));
            }

            // Orientation vers le curseur
            Maths::Vector2<float> finalPos = GetOwner()->GetPosition();
            Maths::Vector2i mousePos = InputModule::GetMousePosition();
            float dx = static_cast<float>(mousePos.x) - finalPos.x;
            float dy = static_cast<float>(mousePos.y) - finalPos.y;
            GetOwner()->SetRotation(sf::degrees(std::atan2(dy, dx) * (180.f / 3.14159f)));

            if (InputModule::GetKeyDown(sf::Keyboard::Key::Escape))
                Engine::GetInstance()->RequestQuit();
        }

        float speed = 300.0f;
    };
}