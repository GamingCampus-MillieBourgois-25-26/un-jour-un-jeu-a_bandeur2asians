#pragma once
#include <cmath>
#include <random>
#include "Core/Component.h"
#include "AssetsModule.h"
#include "SpriteRenderer.h"
#include "Texture.h"
#include "Projectile.h"
#include "Health.h"

namespace TDS
{
    // Positions des box (même grille que Map.h) pour éviter de spawner dessus
    static const int SPAWN_GRID[15][20] =
    {
        { 1,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0 },
        { 1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,1 },
        { 1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0 },
        { 1,1,1,1,1,1,1,0,1,0,0,1,0,0,0,0,0,1,0,0 },
        { 1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0 },
        { 1,1,1,1,1,1,1,0,0,1,0,0,0,0,1,0,0,0,1,0 },
        { 1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0 },
        { 1,1,1,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0 },
        { 1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,1,0 },
        { 1,1,1,1,1,1,1,0,0,1,0,0,0,0,1,0,0,0,0,0 },
        { 1,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0 },
        { 1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,0,0 },
        { 1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,1,0,0 },
        { 1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0 },
        { 1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0 },
    };

    static Maths::Vector2f GetRandomSpawnPos()
    {
        static std::mt19937 rng(std::random_device{}());

        std::vector<Maths::Vector2f> validPos;
        for (int row = 1; row < 14; row++)
            for (int col = 1; col < 19; col++)
                if (SPAWN_GRID[row][col] == 0)
                    validPos.push_back({ col * 64.f + 32.f, row * 64.f + 32.f });

        std::uniform_int_distribution<int> dist(0, (int)validPos.size() - 1);
        return validPos[dist(rng)];
    }

    class Enemy : public Component
    {
    public:
        float speed = 150.f;
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
            // Vérif mort
            Health* hp = GetOwner()->GetComponent<Health>();
            if (hp && hp->IsDead())
            {
                // Respawn
                GetOwner()->SetPosition(GetRandomSpawnPos());
                hp->Reset();
                return;
            }

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
                Texture* tex = am->LoadAsset<Texture>("TDS_Projectile.png");

                GameObject* projectile = GetOwner()->GetScene()->CreateGameObject("Enemy");
                projectile->SetPosition(myPos);
                projectile->CreateComponent<SpriteRenderer>(tex);
                projectile->CreateComponent<Projectile>(sf::radians(std::atan2(dy, dx)), true);
            }
        }
    };
}