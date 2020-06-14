#include "Game.h"

Game::Game(int height, int width, int scale, float padding, int startTiles)
    : height{ height }, width{ width }, padding{ padding }, tiles(width, std::vector<Tile>(height)), scale{ scale }, startTiles{ startTiles }, undoStates{}, yOffset{ scale / 2 }
{
    if (!font.loadFromFile("ClearSans-Bold.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }
    init();

    std::ifstream file("highscore");

    if (!file.fail()) {
        file >> best;
    }
}

sf::Color Game::getTileColor(int value) {
    unsigned int colors[] = {
        0,
        0xeee4daff, // 2
        0xede0c8ff, // 4
        0xf2b179ff, // 8
        0xf59563ff, // 16 ...
        0xf67c5fff,
        0xf65e3bff,
        0xedcf72ff,
        0xedcc61ff,
        0xedc850ff,
        0xedc53fff,
        0xedc22eff
    };

    if (value == 0) { // empty
        return sf::Color(0xeee4da59);
    }

    int log = std::log2(value);

    if (log >= (sizeof(colors) / sizeof(colors[0]))) { // super > 2048
        return sf::Color(0x3c3a32ff);
    }

    return sf::Color(colors[log]);
}

sf::Color Game::getTextColor(int value) {
    if (value >= 8) {
        return sf::Color(0xf9f6f2ff);
    }

    return sf::Color(0x776e65ff);
}

UndoState Game::getUndoState() {
    return { tiles, randomGenerator.getSeed(), score };
}

void Game::setState(UndoState state) {
    tiles = state.tiles;
    randomGenerator.setSeed(state.seed);
    score = state.score;
}

void Game::pushUndoState() {
    undoStates.push_back(getUndoState());
    undoLoc++;
}

void Game::init() {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            tiles[x][y] = Tile(x, y, 0);
        }
    }
    for (int i = 0; i < startTiles; i++) {
        spawnTile();
    }
    undoStates.clear();
    undoLoc = -1;
    animLoc = 0;
    score = 0;
    pushUndoState();
}

void Game::restart() {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            tiles[x][y].remove();
        }
    }
    init();
}

std::vector<Tile*> Game::getFreeTiles() {
    std::vector<Tile*> free;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (tiles[x][y].get_value() == 0) {
                free.push_back(&tiles[x][y]);
            }
        }
    }
    return free;
}

void Game::spawnTile() {
    int value = (randomGenerator.rand() % 10 < 9) ? 2 : 4;
    std::vector<Tile*> free = getFreeTiles();
    if (free.size() == 0) {
        return;
    }
    free[randomGenerator.rand() % free.size()]->spawn(value);
}

float Game::interpolateClamped(float from, float to, float factor) {
    if (factor < 0) {
        factor = 0;
    } else if (factor > 1) {
        factor = 1;
    }

    return from + (to - from) * factor;
}

void Game::renderTile(int value, float xPos, float yPos, sf::RenderWindow& window) {
    sf::RectangleShape rectangle({ scale - padding * 2, scale - padding * 2 });
    rectangle.setFillColor(getTileColor(value));
    rectangle.setPosition(xOffset + xPos * scale + padding, yOffset + yPos * scale + padding);
    window.draw(rectangle);

    if (value != 0) {
        renderText(
            std::to_string(value),
            xOffset + (xPos + .5) * scale,
            yOffset + (yPos + .5) * scale,
            scale / (1 + std::floor(std::log10(value))),
            getTextColor(value),
            window,
            TextAlignment::Center
        );
    }
}

void Game::renderText(const std::string& text, float xPos, float yPos, int size, sf::Color color, sf::RenderWindow& window, TextAlignment alignment, int outline, sf::Color outlineColor) {
    sf::Text sfText;
    sfText.setFont(font);
    sfText.setString(text);
    sfText.setCharacterSize(size);
    sfText.setFillColor(color);
    sfText.setPosition(xPos, yPos);
    sfText.setOutlineThickness(outline);
    sfText.setOutlineColor(outlineColor);

    sf::FloatRect textRect = sfText.getLocalBounds();
    if (alignment == TextAlignment::Center) {
        sfText.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
    } else if (alignment == TextAlignment::Right) {
        sfText.setOrigin(textRect.left + textRect.width, 0);
    }

    window.draw(sfText);
}

void Game::render(sf::RenderWindow& window) {
    window.clear(sf::Color(0xbbada0ff));

    int textSize = std::min(scale * width / 13., scale / 2.1);

    renderText("Score: " + std::to_string(score), padding, padding, textSize, sf::Color::White, window);
    renderText("Best: " + std::to_string(best), scale * width - padding, padding, textSize, sf::Color::White, window, TextAlignment::Right);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            renderTile(0, x, y, window);
        }
    }

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            //std::cout << animLoc << " " << undoLoc << std::endl;

            bool reverse = animLoc > undoLoc;

            auto& drawTiles = undoStates[reverse ? undoLoc : animLoc].tiles;
            auto& nextTiles = undoStates[reverse ? animLoc : undoLoc].tiles;
            Tile& tile = drawTiles[x][y];
            int xTo = nextTiles[x][y].getXMergedTo();
            int yTo = nextTiles[x][y].getYMergedTo();
            Tile& nextTile = nextTiles[x][y];

            int value = tile.get_value();
            int nextValue = nextTile.get_value();
            auto time = animClock.getElapsedTime();
            float seconds = time.asSeconds();
            float factor = seconds * 10;

            int xFrom = x, yFrom = y;

            if (reverse) {
                std::swap(xFrom, xTo);
                std::swap(yFrom, yTo);
            }

            float xPos = interpolateClamped(xFrom, xTo, factor);
            float yPos = interpolateClamped(yFrom, yTo, factor);

            if (factor > 1) { // still
                if (reverse) {
                    std::swap(nextValue, value);
                }
                if (nextValue == 0) {
                    continue;
                }
                renderTile(nextValue, x, y, window);
            } else { // in animation
                if (value == 0) {
                    continue;
                }
                renderTile(value, xPos, yPos, window);
            }
        }
    }

    if (isGameOver()) {
        renderText(
            "Game Over!",
            (xOffset + scale * width) / 2,
            (yOffset + scale * height) / 2,
            scale * width / 10,
            sf::Color(0x776e65ff),
            window,
            TextAlignment::Center,
            padding * 2,
            sf::Color::White
        );
    }
}

bool Game::isGameOver() {
    return !(move( 0, -1, true) ||
             move( 0,  1, true) ||
             move(-1,  0, true) ||
             move( 1,  0, true));
}

void Game::addScore(int value) {
    score += value;
    if (score > best) {
        best = score;
    }
}

bool Game::move(int xDir, int yDir, bool dryRun) {
    UndoState original = getUndoState();

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            tiles[x][y].reset();
        }
    }

    int farthest = tiles.size() - 1;
    bool moved = false;
    for (int x = (xDir < 0) ? 0 : farthest; x >= 0 && x <= farthest; x -= (xDir ? xDir : 1)) {
        for (int y = (yDir < 0) ? 0 : farthest; y >= 0 && y <= farthest; y -= (yDir ? yDir : 1)) {
            Tile& tile = tiles[x][y];
            int value = tile.get_value();

            if (value == 0) {
                continue;
            }

            Tile* lastEmpty = nullptr;
            for (int xNext = x + xDir, yNext = y + yDir; xNext >= 0 && xNext <= farthest && yNext >= 0 && yNext <= farthest; xNext += xDir, yNext += yDir) {
                Tile& nextTile = tiles[xNext][yNext];
                if (nextTile.get_value() == value) {
                    moved = true;
                    nextTile.mergeWith(tile);
                    addScore(value * 2);
                    lastEmpty = nullptr;
                    break;
                } else if (nextTile.get_value() == 0) {
                    lastEmpty = &nextTile;
                } else {
                    break;
                }
            }
            if (lastEmpty) {
                moved = true;
                lastEmpty->mergeWith(tile);
            }
        }
    }

    if (dryRun) {
        setState(original);
        return moved;
    }

    if (moved) {
        spawnTile();

        animClock.restart();

        pushUndoState();
        animLoc = undoLoc - 1;
    }

    return moved;
}

void Game::undo() {
    if (undoLoc == 0) {
        return;
    }
    undoLoc--;
    setState(undoStates[undoLoc]);

    animClock.restart();
    animLoc = undoLoc + 1;
}

void Game::redo() {
    if (undoLoc == undoStates.size() - 1) {
        return;
    }
    undoLoc++;
    setState(undoStates[undoLoc]);

    animClock.restart();
    animLoc = undoLoc - 1;
}

void Game::close() {
    std::ofstream fs("highscore", std::ios::trunc);
    fs << best;
}
