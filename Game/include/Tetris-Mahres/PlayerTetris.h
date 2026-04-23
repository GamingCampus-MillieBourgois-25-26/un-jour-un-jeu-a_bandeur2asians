#pragma once

#include "Core/Component.h"
#include "InputModule.h"

#include <cmath>

namespace TETRIS
{
    class Player : public Component
    {
    public:
        void Update(const float _delta_time) override
        {
            Maths::Vector2<float> position = GetOwner()->GetPosition();

            if (InputModule::GetKeyDown(sf::Keyboard::Key::D))
                position.x += cellSize;
            
            if (InputModule::GetKeyDown(sf::Keyboard::Key::Q))
                position.x -= cellSize;
            
            if (InputModule::GetKeyDown(sf::Keyboard::Key::S))
                position.y += cellSize;

            if (InputModule::GetKeyDown(sf::Keyboard::Key::R))
            {
                sf::Angle currentRotation = GetOwner()->GetRotation();
                GetOwner()->SetRotation(currentRotation + sf::degrees(angleRotation));
            }

            GetOwner()->SetPosition(position);
        }

        float cellSize = 32.0f;
        float angleRotation = 90.0f;
        sf::Color color;
        Maths::Vector2i size;
    };
}