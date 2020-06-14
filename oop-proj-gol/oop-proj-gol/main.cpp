#include <vector>
#include <array>
#include <unordered_map>
#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameOfLife.hpp"

int main() {
    srand((unsigned int)time(NULL));
    int width = 400, height = 200, scale = 4, n_tribes = 4;
    //int width = rand() % 400, height = rand() % 200, scale = 4, n_tribes = rand() % 10;
    bool paused = false;
    bool mouse_pressed = false;
    GameOfLife game(height, width, n_tribes, scale);
    sf::RenderWindow window(sf::VideoMode(width * scale, height * scale), "Game of life");
    window.setFramerateLimit(60);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                mouse_pressed = true;
            } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                mouse_pressed = false;
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::P) {
                    paused = !paused;
                } else if (event.key.code == sf::Keyboard::N) {
                    game.update();
                } else if (event.key.code == sf::Keyboard::T) {
                    game.switch_click_tribe();
                } else if (event.key.code == sf::Keyboard::X) {
                    game.switch_click_kill();
                }
            }
        }
        if (mouse_pressed) {
            auto [mx, my] = sf::Mouse::getPosition(window);
            game.click(mx / scale, my / scale);
        }
        
        if (!paused) {
            game.update();
        }
        window.clear();
        game.render(window);
        window.display();
    }

    return 0;
}