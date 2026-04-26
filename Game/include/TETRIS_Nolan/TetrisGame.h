#pragma once
#include <array>
#include <vector>
#include <random>
#include <cmath>
#include "Core/Component.h"
#include "RectangleShapeRenderer.h"
#include "InputModule.h"

namespace Tetris
{
    static const int COLS = 10;
    static const int ROWS = 20;
    static const float CELL = 32.f;

    static const std::vector<std::vector<std::vector<int>>> PIECES =
    {
        { {1,1,1,1} },                              // I
        { {1,1}, {1,1} },                           // O
        { {0,1,0}, {1,1,1} },                       // T
        { {0,1,1}, {1,1,0} },                       // S
        { {1,1,0}, {0,1,1} },                       // Z
        { {1,0,0}, {1,1,1} },                       // J
        { {0,0,1}, {1,1,1} },                       // L
    };

    static const sf::Color COLORS[] =
    {
        sf::Color::Cyan,
        sf::Color::Yellow,
        sf::Color(128,0,128), // Violet
        sf::Color::Green,
        sf::Color::Red,
        sf::Color::Blue,
        sf::Color(255,165,0), // Orange
    };

    class TetrisGame : public Component
    {
    public:
        void Awake() override
        {
            // Grille vide
            for (int r = 0; r < ROWS; r++)
                for (int c = 0; c < COLS; c++)
                    m_grid[r][c] = -1;

            // Créer les cellules visuelles de la grille
            for (int r = 0; r < ROWS; r++)
            {
                for (int c = 0; c < COLS; c++)
                {
                    GameObject* cell = GetOwner()->GetScene()->CreateGameObject("Cell");
                    cell->SetPosition({ c * CELL + CELL * 0.5f + m_offsetX,
                                        r * CELL + CELL * 0.5f + m_offsetY });
                    RectangleShapeRenderer* rsr = cell->CreateComponent<RectangleShapeRenderer>();
                    rsr->SetSize({ CELL - 1.f, CELL - 1.f });
                    rsr->SetColor(sf::Color(40, 40, 40));
                    m_cellObjects[r][c] = cell;
                }
            }

            SpawnPiece();
        }

        void Update(const float _delta_time) override
        {
            // Déplacement gauche/droite
            if (InputModule::GetKeyDown(sf::Keyboard::Key::Left))
                MovePiece(-1, 0);
            if (InputModule::GetKeyDown(sf::Keyboard::Key::Right))
                MovePiece(1, 0);
            if (InputModule::GetKeyDown(sf::Keyboard::Key::Up))
                RotatePiece();
            if (InputModule::GetKey(sf::Keyboard::Key::Down))
                m_fallInterval = 0.05f;
            else
                m_fallInterval = 0.5f;
            
            // Chute automatique
            m_fallTimer += _delta_time;
            if (m_fallTimer >= m_fallInterval)
            {
                m_fallTimer = 0.f;
                if (!MovePiece(0, 1))
                    LockPiece();
            }

            RefreshVisuals();
        }
        float angleRotation = 90.0f;

    private:
        int   m_grid[ROWS][COLS];
        GameObject* m_cellObjects[ROWS][COLS];

        std::vector<std::vector<int>> m_currentPiece;
        int m_pieceX = 0;
        int m_pieceY = 0;
        int m_pieceColor = 0;

        float m_fallTimer = 0.f;
        float m_fallInterval = 0.5f;
        float m_offsetX = 160.f; // centrage horizontal
        float m_offsetY = 16.f;

        std::mt19937 m_rng{ std::random_device{}() };

        void SpawnPiece()
        {
            std::uniform_int_distribution<int> dist(0, (int)PIECES.size() - 1);
            int idx = dist(m_rng);
            m_currentPiece = PIECES[idx];
            m_pieceColor = idx;
            m_pieceX = COLS / 2 - (int)m_currentPiece[0].size() / 2;
            m_pieceY = 0;

           
            if (!IsValid(m_currentPiece, m_pieceX, m_pieceY))
            {
                // Reset grille
                for (int r = 0; r < ROWS; r++)
                    for (int c = 0; c < COLS; c++)
                        m_grid[r][c] = -1;
            }
        }

        bool IsValid(const std::vector<std::vector<int>>& piece, int px, int py)
        {
            for (int r = 0; r < (int)piece.size(); r++)
                for (int c = 0; c < (int)piece[r].size(); c++)
                    if (piece[r][c])
                    {
                        int gr = py + r;
                        int gc = px + c;
                        if (gc < 0 || gc >= COLS || gr >= ROWS) return false;
                        if (gr >= 0 && m_grid[gr][gc] != -1) return false;
                    }
            return true;
        }

        bool MovePiece(int dx, int dy)
        {
            if (IsValid(m_currentPiece, m_pieceX + dx, m_pieceY + dy))
            {
                m_pieceX += dx;
                m_pieceY += dy;
                return true;
            }
            return false;
        }

        void RotatePiece()
        {
            int rows = (int)m_currentPiece.size();
            int cols = (int)m_currentPiece[0].size();
            std::vector<std::vector<int>> rotated(cols, std::vector<int>(rows));
            for (int r = 0; r < rows; r++)
                for (int c = 0; c < cols; c++)
                    rotated[c][rows - 1 - r] = m_currentPiece[r][c];
            if (IsValid(rotated, m_pieceX, m_pieceY))
                m_currentPiece = rotated;
        }

        void LockPiece()
        {
            for (int r = 0; r < (int)m_currentPiece.size(); r++)
                for (int c = 0; c < (int)m_currentPiece[r].size(); c++)
                    if (m_currentPiece[r][c])
                        m_grid[m_pieceY + r][m_pieceX + c] = m_pieceColor;

            ClearLines();
            SpawnPiece();
        }

        void ClearLines()
        {
            for (int r = ROWS - 1; r >= 0; r--)
            {
                bool full = true;
                for (int c = 0; c < COLS; c++)
                    if (m_grid[r][c] == -1) { full = false; break; }

                if (full)
                {
                    // Décaler tout vers le bas
                    for (int row = r; row > 0; row--)
                        for (int c = 0; c < COLS; c++)
                            m_grid[row][c] = m_grid[row - 1][c];
                    for (int c = 0; c < COLS; c++)
                        m_grid[0][c] = -1;
                    r++; // revérifier la même ligne
                }
            }
        }

        void RefreshVisuals()
        {
            // Grille fixe
            for (int r = 0; r < ROWS; r++)
                for (int c = 0; c < COLS; c++)
                {
                    RectangleShapeRenderer* rsr = m_cellObjects[r][c]->GetComponent<RectangleShapeRenderer>();
                    if (!rsr) continue;
                    rsr->SetColor(m_grid[r][c] == -1 ? sf::Color(40, 40, 40) : COLORS[m_grid[r][c]]);
                }

            // Pièce courante
            for (int r = 0; r < (int)m_currentPiece.size(); r++)
                for (int c = 0; c < (int)m_currentPiece[r].size(); c++)
                    if (m_currentPiece[r][c])
                    {
                        int gr = m_pieceY + r;
                        int gc = m_pieceX + c;
                        if (gr >= 0 && gr < ROWS && gc >= 0 && gc < COLS)
                        {
                            RectangleShapeRenderer* rsr = m_cellObjects[gr][gc]->GetComponent<RectangleShapeRenderer>();
                            if (rsr) rsr->SetColor(COLORS[m_pieceColor]);
                        }
                    }
        }
    };
}