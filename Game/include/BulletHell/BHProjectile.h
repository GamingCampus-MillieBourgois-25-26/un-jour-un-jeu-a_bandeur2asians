#pragma once
#include <cmath>
#include "Core/Component.h"
#include "BHHealth.h"
#include "SpriteRenderer.h"

namespace BulletHell
{
    class BHProjectile : public Component
    {
    public:
        BHProjectile(sf::Angle angle, bool fromBoss)
            : m_angle(angle), m_fromBoss(fromBoss) {
        }

        float speed = 500.f;

        void Update(const float _delta_time) override
        {
            Maths::Vector2f pos = GetOwner()->GetPosition();
            pos.x += std::cos(m_angle.asRadians()) * speed * _delta_time;
            pos.y += std::sin(m_angle.asRadians()) * speed * _delta_time;
            GetOwner()->SetPosition(pos);

            // Hors écran
            if (pos.x < 0 || pos.x > 1280 || pos.y < 0 || pos.y > 960)
            {
                GetOwner()->MarkForDeletion();
                return;
            }

            // Collision
            std::string target = m_fromBoss ? "Player" : "Boss";
            auto& objects = GetOwner()->GetScene()->GetGameObjects();
            for (auto& go : objects)
            {
                if (go->GetName() != target) continue;
                Maths::Vector2f tPos = go->GetPosition();
                float dx = pos.x - tPos.x;
                float dy = pos.y - tPos.y;
                if (std::sqrt(dx * dx + dy * dy) < 32.f)
                {
                    Health* hp = go->GetComponent<Health>();
                    if (hp) hp->TakeDamage(m_fromBoss ? 15.f : 25.f);
                    GetOwner()->MarkForDeletion();
                    break;
                }
            }
        }

    private:
        sf::Angle m_angle;
        bool      m_fromBoss;
    };
}