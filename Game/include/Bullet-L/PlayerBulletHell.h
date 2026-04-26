#pragma once

#include "Bullets.h"

#include "Core/Component.h"
#include "InputModule.h"

#include <cmath>

namespace HELL
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

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
            {
                AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
                Texture* projectile_texture = assets_module->LoadAsset<Texture>("TankBulletPlayer.png");

                GameObject* projectile = GetOwner()->GetScene()->CreateGameObject("Projectile");
                projectile->SetPosition(position);
                projectile->CreateComponent<SpriteRenderer>(projectile_texture);
                projectile->CreateComponent<Projectile>(sf::degrees(0.f));
            }
            GetOwner()->SetPosition(position);
        }

        float speed = 300.0f;
    };
}
