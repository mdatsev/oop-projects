#include <SFML/Graphics.hpp>

#include "Game.h"

int main() {
    int boardSize = 4;
    int padding = 2;
    int windowWidth = 400;
    int windowHeight = windowWidth;

    Game game(boardSize, boardSize, windowHeight / boardSize, padding);

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight + windowHeight / boardSize / 2), "2048");
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                game.close();
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    game.move(0, -1);
                } else if (event.key.code == sf::Keyboard::Down) {
                    game.move(0, 1);
                } else if (event.key.code == sf::Keyboard::Left) {
                    game.move(-1, 0);
                } else if (event.key.code == sf::Keyboard::Right) {
                    game.move(1, 0);
                } else if (event.key.code == sf::Keyboard::R) {
                    game.restart();
                } else if (event.key.code == sf::Keyboard::U) {
                    game.undo();
                } else if (event.key.code == sf::Keyboard::Y) {
                    game.redo();
                }
            }
        }
        std::cout << 1 / clock.restart().asSeconds() << std::endl;
        window.clear();
        game.render(window);
        window.display();
    }

    return 0;
}