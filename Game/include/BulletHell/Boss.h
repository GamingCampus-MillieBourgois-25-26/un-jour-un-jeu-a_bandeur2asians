#pragma once
#include <cmath>
#include "Core/Component.h"
#include "AssetsModule.h"
#include "SpriteRenderer.h"
#include "Texture.h"
#include "BHHealth.h"
#include <BulletHell/BHProjectile.h>

namespace BulletHell
{
    class Boss : public Component
    {
    public:
        int   bulletCount = 12;    // balles par cercle
        float fireRate = 1.5f;  // secondes entre chaque salve
        float angleOffset = 0.f;   // rotation du pattern à chaque salve

    private:
        float m_fireTimer = 0.f;

    public:
        void Update(const float _delta_time) override
        {
            Health* hp = GetOwner()->GetComponent<Health>();
            if (hp && hp->IsDead())
            {
                GetOwner()->MarkForDeletion();
                return;
            }

            m_fireTimer += _delta_time;
            if (m_fireTimer >= fireRate)
            {
                m_fireTimer = 0.f;
                FireCircle();
                angleOffset += 15.f; // décale le cercle à chaque salve
            }
        }

    private:
        void FireCircle()
        {
            AssetsModule* assets = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
            Texture* tex = assets->LoadAsset<Texture>("BHprojectile.png");

            Maths::Vector2f pos = GetOwner()->GetPosition();
            float step = 360.f / bulletCount;

            for (int i = 0; i < bulletCount; i++)
            {
                float deg = angleOffset + step * i;
                float rad = deg * (3.14159f / 180.f);

                GameObject* bullet = GetOwner()->GetScene()->CreateGameObject("BossBullet");
                bullet->SetPosition(pos);
                bullet->CreateComponent<SpriteRenderer>(tex);
                bullet->CreateComponent<BHProjectile>(sf::radians(rad), true);
            }
        }
    };
}