#pragma once

#include <vector>
#include <array>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Cell.hpp"
#include "Tribe.hpp"

const sf::Color DEAD_COLOR{ 0, 0, 0 };
class GameOfLife
{
private:
    int height, width, cell_size;
    std::vector<Cell> cells;
    std::unordered_map<int, Tribe> tribes;
    bool click_kill;
    int click_tribe;

    sf::Color random_tribe_color();

    int loop_coord(int n, int max);

    Cell& get_cell(std::vector<Cell>& cells, int x, int y);

    std::array<Cell, 8> get_neighbours(std::vector<Cell>& cells, int x, int y);

    Cell get_new_cell_state(Cell cell, const std::array<Cell, 8>& neighs);

public:
    GameOfLife(int height, int width, int n_tribes, int cell_size);

    void update();

    void render(sf::RenderWindow& window);

    void click(int x, int y);

    void switch_click_tribe();

    void switch_click_kill();
};