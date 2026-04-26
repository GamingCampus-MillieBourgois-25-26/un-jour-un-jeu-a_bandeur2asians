#pragma once
#include <cmath>
#include "Core/Component.h"
#include "InputModule.h"
#include "AssetsModule.h"
#include "SpriteRenderer.h"
#include "Texture.h"
#include "BHHealth.h"
#include <BulletHell/BHProjectile.h>

namespace BulletHell
{
    class BHPlayer : public Component
    {
    public:
        float speed = 300.f;

        void Update(const float _delta_time) override
        {
            Maths::Vector2f pos = GetOwner()->GetPosition();

            if (InputModule::GetKey(sf::Keyboard::Key::D)) pos.x += speed * _delta_time;
            if (InputModule::GetKey(sf::Keyboard::Key::Q)) pos.x -= speed * _delta_time;
            if (InputModule::GetKey(sf::Keyboard::Key::Z)) pos.y -= speed * _delta_time;
            if (InputModule::GetKey(sf::Keyboard::Key::S)) pos.y += speed * _delta_time;

            // Limites écran
            pos.x = std::max(32.f, std::min(pos.x, 1248.f));
            pos.y = std::max(32.f, std::min(pos.y, 928.f));

            GetOwner()->SetPosition(pos);

            // Orientation vers curseur
            Maths::Vector2i mouse = InputModule::GetMousePosition();
            float dx = static_cast<float>(mouse.x) - pos.x;
            float dy = static_cast<float>(mouse.y) - pos.y;
            GetOwner()->SetRotation(sf::degrees(std::atan2(dy, dx) * (180.f / 3.14159f)));

            // Tir
            if (InputModule::GetKeyDown(sf::Keyboard::Key::Space))
            {
                AssetsModule* assets = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
                Texture* tex = assets->LoadAsset<Texture>("BHPlayerProj.png");

                GameObject* p = GetOwner()->GetScene()->CreateGameObject("PlayerBullet");
                p->SetPosition(pos);
                p->CreateComponent<SpriteRenderer>(tex);
                p->CreateComponent<BHProjectile>(sf::radians(std::atan2(dy, dx)), false);
            }

            // Mort
            Health* hp = GetOwner()->GetComponent<Health>();
            if (hp && hp->IsDead())
                Engine::GetInstance()->RequestQuit();

            if (InputModule::GetKeyDown(sf::Keyboard::Key::Escape))
                Engine::GetInstance()->RequestQuit();
        }
    };
}