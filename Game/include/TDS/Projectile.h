#pragma once
#include <cmath>
#include "Core/Component.h"
#include "InputModule.h"
#include "Health.h"

namespace TDS
{
    class Projectile : public Component
    {
    public:
        Projectile(sf::Angle a, bool fromEnemy = false)
            : angle(a), m_fromEnemy(fromEnemy) {
        }

        float speed = 400.f;

        void Update(const float _delta_time) override
        {
            Maths::Vector2f pos = GetOwner()->GetPosition();
            Maths::Vector2f dir = { std::cos(angle.asRadians()), std::sin(angle.asRadians()) };
            pos += dir * speed * _delta_time;
            GetOwner()->SetPosition(pos);

            // Détection collision
            auto& objects = GetOwner()->GetScene()->GetGameObjects();
            for (auto& go : objects)
            {
                if (go.get() == GetOwner()) continue;

                // Cible : joueur si projectile ennemi, ennemi si projectile joueur
                std::string targetName = m_fromEnemy ? "Player" : "Enemy";
                if (go->GetName() != targetName) continue;

                Maths::Vector2f targetPos = go->GetPosition();
                float dx = pos.x - targetPos.x;
                float dy = pos.y - targetPos.y;
                float dist = std::sqrt(dx * dx + dy * dy);

                if (dist < 32.f) // rayon de hit
                {
                    Health* hp = go->GetComponent<Health>();
                    if (hp) hp->TakeDamage(15.f);
                    GetOwner()->MarkForDeletion();
                    break;
                }
            }

            // Destruction hors map
            if (pos.x < 0 || pos.x > 1280 || pos.y < 0 || pos.y > 960)
                GetOwner()->MarkForDeletion();
        }

    private:
        sf::Angle angle;
        bool m_fromEnemy = false;
    };
}