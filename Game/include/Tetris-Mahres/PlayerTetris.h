#pragma once

#include "Core/Component.h"
#include "InputModule.h"
#include "WindowModule.h"
#include <cmath>
#include <array>

namespace TETRIS
{
    class Player : public Component
    {
    public:
        void Awake() override
        {
            WindowModule* window = Engine::GetInstance()->GetModuleManager()->GetModule<WindowModule>();
            Maths::Vector2u windowSize = window->GetSize();
            m_windowWidth = static_cast<float>(windowSize.x);
            m_windowHeight = static_cast<float>(windowSize.y);
        }

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

            m_fallTimer += _delta_time;
            if (m_fallTimer >= m_fallInterval)
            {

                m_fallTimer = 0.f;

                if (position.y + cellSize < m_windowHeight)

                    position.y += cellSize;

                else
                    LockPiece(position);
            }

                if (position.y <= 0.f && m_needsNewPiece)
                    ResetGame();

                GetOwner()->SetPosition(position);
            
        }

            float cellSize = 32.0f;
            float angleRotation = 90.0f;
            sf::Color color;
            Maths::Vector2i size;
            bool m_needsNewPiece = false;

        private:
            float m_fallTimer = 0.f;
            float m_fallInterval = 1.0f;
            float m_windowWidth = 600.f;
            float m_windowHeight = 600.f;

            // Grille partagée entre toutes les pièces
            static inline bool m_grid[20][10] = {};

            void LockPiece(const Maths::Vector2<float>&position)
            {
                int gridX = static_cast<int>(position.x / cellSize);
                int gridY = static_cast<int>(position.y / cellSize);

                int cols = static_cast<int>(m_windowWidth / cellSize);
                int rows = static_cast<int>(m_windowHeight / cellSize);

                if (gridX >= 0 && gridX < cols && gridY >= 0 && gridY < rows)
                    m_grid[gridY][gridX] = true;

                ClearLines();
                m_needsNewPiece = true;
            }

            void ClearLines()
            {
                int cols = static_cast<int>(m_windowWidth / cellSize);
                int rows = static_cast<int>(m_windowHeight / cellSize);

                for (int r = rows - 1; r >= 0; r--)
                {
                    bool full = true;
                    for (int c = 0; c < cols; c++)
                        if (!m_grid[r][c]) { full = false; break; }

                    if (full)
                    {
                        for (int row = r; row > 0; row--)
                            for (int c = 0; c < cols; c++)
                                m_grid[row][c] = m_grid[row - 1][c];

                        for (int c = 0; c < cols; c++)
                            m_grid[0][c] = false;

                        r++;
                    }
                }
            }

            void ResetGame()
            {
                // Vide la grille
                int cols = static_cast<int>(m_windowWidth / cellSize);
                int rows = static_cast<int>(m_windowHeight / cellSize);

                for (int r = 0; r < rows; r++)
                    for (int c = 0; c < cols; c++)
                        m_grid[r][c] = false;

                m_needsNewPiece = true;
            }
    };
}