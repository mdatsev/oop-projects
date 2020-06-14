#pragma once

#include <SFML/Graphics.hpp>

class Tribe
{
private:
    sf::Color color;
public:
    Tribe(sf::Color color);

    sf::Color get_color();
};