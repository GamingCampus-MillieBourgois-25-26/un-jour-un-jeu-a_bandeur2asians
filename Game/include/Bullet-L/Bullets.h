#pragma once
#include "Core/Component.h"
#include "InputModule.h"

namespace HELL
{
    class Projectile : public Component
    {
    private:
        sf::Angle angle;
    public:
        Projectile(sf::Angle a) { angle = a; }
        float speed = 50.0f;

        void Update(const float _delta_time) override
        {
            Maths::Vector2<float> position = GetOwner()->GetPosition();
            Maths::Vector2f dir = { cos(angle.asRadians()), sin(angle.asRadians()) };
            position += dir * speed * _delta_time;
            GetOwner()->SetPosition(position);
        }
    };
}
