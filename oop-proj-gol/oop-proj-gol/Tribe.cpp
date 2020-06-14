#include "Tribe.hpp"

sf::Color Tribe::get_color() {
    return color;
}

Tribe::Tribe(sf::Color color) : color{ color } {

}