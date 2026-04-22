#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

namespace DTS
{
    class Background
    {
    public:
        Background();

        bool loadFromFile(const std::string& filepath);

    private:
        sf::Texture background;
        std::optional<sf::Sprite> sprite;
    };
}