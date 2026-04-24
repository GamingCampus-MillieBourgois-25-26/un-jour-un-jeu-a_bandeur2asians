#pragma once
#include <cmath>
#include <random>
#include <vector>


#include "Core/Component.h"
#include "AssetsModule.h"
#include "SpriteRenderer.h"
#include "Texture.h"
#include "Bullets.h"
//#include "Health.h"

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

    class Opps
    {
    private:
        float x, y;
        OppsType type;
        std::optional<sf::Sprite> sprite;
        int health;  // Points de vie de l'ennemi

        // Comportement
        sf::Clock shootClock;
        float moveTimer;

        // Textures statiques
        static sf::Texture textureTank1;
        static sf::Texture textureTank2;
        static sf::Texture textureTank3;
        static sf::Texture textureTank4;
        static sf::Texture textureTank5;

        static bool texturesLoaded;

    public:
        Opps(float startX, float startY, OppsType type);

        void update(float playerX, float playerY, Projectile& projectileManager);
        void draw(sf::RenderWindow& window);

        sf::Vector2f getPosition() const;
        sf::FloatRect getBounds() const;
        sf::FloatRect getHitbox() const;
        OppsType getType() const;

        
        int getHealth() const { return health; }
        void takeDamage(int damage);
        bool isAlive() const { return health > 0; }

        
        static void loadTextures();
    };

    class ProjectileManager
    {
    private:
        std::vector<Projectile> projectiles;

    public:
        ProjectileManager();

        // Nouvelle signature avec speedX et speedY
        void addProjectile(float x, float y, Projectile type, float speedX = 0.0f, float speedY = -5.0f);
        void update();
        void draw(sf::RenderWindow& window);
        std::vector<Projectile>& getProjectiles();
        void removeProjectile(size_t index);
    };

}