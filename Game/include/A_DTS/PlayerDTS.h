#pragma once

#include "ProjectilesDTS.h"

#include "Core/Component.h"
#include "InputModule.h"

#include <cmath>

namespace DTS
{
    class Player : public Component
    {
    public:
        void Update(const float _delta_time) override
        {
            Maths::Vector2<float> position = GetOwner()->GetPosition();

            if (InputModule::GetKey(sf::Keyboard::Key::D))
            {
                position.x += speed * _delta_time;
            }
            if (InputModule::GetKey(sf::Keyboard::Key::Q))
            {
                position.x -= speed * _delta_time;
            }

            if (InputModule::GetKey(sf::Keyboard::Key::Z))
            {
                position.y -= speed * _delta_time;
            }
            if (InputModule::GetKey(sf::Keyboard::Key::S))
            {
                position.y += speed * _delta_time;
            }

            GetOwner()->SetPosition(position);


            Maths::Vector2i mousePos = InputModule::GetMousePosition();
            float dx = static_cast<float>(mousePos.x) - position.x;
            float dy = static_cast<float>(mousePos.y) - position.y;
            float angle = std::atan2(dy, dx) * (50.f / 3.14159f);
            GetOwner()->SetRotation(sf::degrees(angle));

            if (InputModule::GetKeyDown(sf::Keyboard::Key::Space))
            {
                AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
                Texture* projectile_texture = assets_module->LoadAsset<Texture>("bullet.png");

                GameObject* projectile = GetOwner()->GetScene()->CreateGameObject("Projectile");
                projectile->SetPosition(position);
                projectile->CreateComponent<SpriteRenderer>(projectile_texture);
                projectile->CreateComponent<Projectile>(sf::radians(atan2(-dy, -dx)));
            }


        }

        float speed = 100.0f;
    };
}
