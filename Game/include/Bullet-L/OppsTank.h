#pragma once
#include <cmath>
#include <random>
#include <vector>


#include "Core/Component.h"
#include "AssetsModule.h"
#include "SpriteRenderer.h"
#include "Texture.h"
#include "Bullets.h"
#include "Life.h"

namespace HELL
{
    enum class OppsType
    {
        TANK1,
        TANK2,
        TANK3,
        TANK4,
        TANK5
    };

    class Opps : public Component
    {
    public:
        float speed = 35.f;
        float detectionRadius = 400.f;
        float fireRate = 1.f;

    private:
        float m_fireTimer = 0.f;

        GameObject* FindPlayer()
        {
            auto& objects = GetOwner()->GetScene()->GetGameObjects();
            for (auto& go : objects)
                if (go->GetName() == "Player")
                    return go.get();
            return nullptr;
        }

    public:
        void Update(const float _delta_time) override
        {
            

            GameObject* player = FindPlayer();
            if (!player) return;

            Maths::Vector2f myPos = GetOwner()->GetPosition();
            Maths::Vector2f playerPos = player->GetPosition();

            float dx = playerPos.x - myPos.x;
            float dy = playerPos.y - myPos.y;
            float dist = std::sqrt(dx * dx + dy * dy);

            if (dist > detectionRadius) return;

            float nx = dx / dist;
            float ny = dy / dist;

            GetOwner()->SetRotation(sf::degrees(std::atan2(dy, dx) * (180.f / 3.14159f)));

            Maths::Vector2f newPos = myPos;
            newPos.x += nx * speed * _delta_time;
            newPos.y += ny * speed * _delta_time;
            GetOwner()->SetPosition(newPos);

            m_fireTimer += _delta_time;
            if (m_fireTimer >= fireRate)
            {
                m_fireTimer = 0.f;

                AssetsModule* am = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
                Texture* tex = am->LoadAsset<Texture>("TankBullet.png");

                GameObject* projectile = GetOwner()->GetScene()->CreateGameObject("Enemy");
                projectile->SetPosition(myPos);
                projectile->CreateComponent<SpriteRenderer>(tex);
                projectile->CreateComponent<Projectile>(sf::radians(std::atan2(dy, dx)));
            }
        }
    };

}