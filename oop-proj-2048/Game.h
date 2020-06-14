#pragma once

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <utility>
#include <fstream>

#include "SFML\Graphics.hpp"
#include "Tile.h"
#include "LCG.h"
#include "UndoState.h"

enum class TextAlignment {
    Left,
    Center,
    Right
};

class Game {
    int height, width, scale;
    std::vector<std::vector<Tile>> tiles;
    const float padding;
    const int xOffset = 0;
    const int yOffset;
    sf::Font font;
    int startTiles;
    std::vector<UndoState> undoStates;
    int undoLoc;
    sf::Clock animClock;
    int animLoc;
    int score;
    int best = 0;
    
    sf::Color getTileColor(int value);

    sf::Color getTextColor(int value);

    UndoState getUndoState();

    void setState(UndoState state);

    void pushUndoState();

    void init();

    std::vector<Tile*> getFreeTiles();

    void spawnTile();

    float interpolateClamped(float from, float to, float factor);

    void renderTile(int value, float xPos, float yPos, sf::RenderWindow& window);

    void renderText(const std::string& text, float xPos, float yPos, int size, sf::Color color, sf::RenderWindow& window, TextAlignment alignment = TextAlignment::Left, int outline = 0, sf::Color outlineColor = {});

    bool isGameOver();

    void addScore(int value);

public:
    Game(int height, int width, int scale, float padding, int startTiles = 2);

    void render(sf::RenderWindow& window);

    bool move(int xDir, int yDir, bool dryRun = false);

    void undo();

    void redo();

    void restart();

    void close();
};

