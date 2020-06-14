#include "GameOfLife.hpp"

GameOfLife::GameOfLife(int height, int width, int n_tribes, int cell_size)
    : height{ height }, width{ width }, cells{ width * height }, cell_size{ cell_size }, click_kill{ false }, click_tribe{ 0 }
{
    for (int i = 0; i < n_tribes; i++) {
        tribes.emplace(std::make_pair(i, Tribe(random_tribe_color())));
    }

    for (auto& cell : cells) {
        if (rand() % 100 < 20) {
            cell.live(rand() % n_tribes);
        }
    }
}

sf::Color GameOfLife::random_tribe_color() {
    const sf::Color first_colors[] = {
        { 0xFF, 0xFF, 0xFF }, { 0xFF, 0x00, 0x00 }, { 0x00, 0xFF, 0x00 }, { 0x00, 0x00, 0xFF },
        { 0xF9, 0xBC, 0x08 }, { 0x00, 0xFF, 0xFF }, { 0xFF, 0xFF, 0x00 }, { 0xFF, 0x00, 0xFF },
        { 0x80, 0x00, 0x00 }, { 0xC0, 0xC0, 0xC0 }, { 0xFE, 0x83, 0xCC }, { 0x80, 0x00, 0x80 },
        { 0x80, 0x80, 0x00 }, { 0x00, 0x80, 0x80 }, { 0x80, 0x80, 0x80 }, { 0x00, 0x80, 0x00 },
        { 0x80, 0x00, 0x00 }, { 0x00, 0x00, 0x80 }
    };

    if (tribes.size() < sizeof(first_colors) / sizeof(first_colors[0])) {
        return first_colors[tribes.size()];
    }

    return { (sf::Uint8)(rand() % 255), (sf::Uint8)(rand() % 255), (sf::Uint8)(rand() % 255) };
}

int GameOfLife::loop_coord(int n, int max) {
    return ((n % max) + max) % max;
}

Cell& GameOfLife::get_cell(std::vector<Cell>& cells, int x, int y) {
    return cells[loop_coord(x, width) + loop_coord(y, height) * width];
}

std::array<Cell, 8> GameOfLife::get_neighbours(std::vector<Cell>& cells, int x, int y) {
    const int neigh_indices[8][2] = {
        { 1,  0 },
        { 0,  1 },
        { -1,  0 },
        { 0, -1 },
        { 1,  1 },
        { -1,  1 },
        { -1, -1 },
        { 1, -1 }
    };
    std::array<Cell, 8> neighs;
    for (int i = 0; i < neighs.size(); i++) {
        neighs[i] = get_cell(cells, x + neigh_indices[i][0], y + neigh_indices[i][1]);
    }
    return neighs;
}

Cell GameOfLife::get_new_cell_state(Cell cell, const std::array<Cell, 8>& neighs) {
    int alive = 0;
    std::unordered_map<int, int> alive_tribes;
    for (int i = 0; i < neighs.size(); i++) {
        if (neighs[i].is_alive()) {
            int tribe_id = neighs[i].get_tribe_id();
            alive++;
            alive_tribes[tribe_id]++;
        }
    }

    if (cell.is_alive()) {
        int same_alive = alive_tribes[cell.get_tribe_id()];
        if (alive < 2) {
            cell.die();
        } else if (alive > 3) {
            cell.die();
        } else if (!(same_alive == 3 || same_alive == 2)) {
            if (rand() % 2) {
                cell.die();
            }
        }
    } else {
        std::vector<int> three_ids;
        for (auto [id, value] : alive_tribes) {
            if (value == 3) {
                three_ids.push_back(id);
            }
        }

        if (three_ids.size() == 1) {
            cell.live(three_ids[0]);
        }

        //if (three_ids.size() > 0) {
        //    cell.live(three_ids[rand() % three_ids.size()]);
        //}
    }

    return cell;
}

void GameOfLife::update() {
    std::vector<Cell> old_cells = cells;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            Cell cell = get_cell(old_cells, x, y);
            std::array<Cell, 8> neighs = get_neighbours(old_cells, x, y);
            get_cell(cells, x, y) = get_new_cell_state(cell, neighs);
        }
    }
}

void GameOfLife::render(sf::RenderWindow& window) {
    sf::VertexArray vao(sf::Quads, cells.size() * 4);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            int cell_index = x + width * y;
            Cell& cell = cells[cell_index];
            for (int i = 0; i < 4; i++) {
                sf::Vertex& vertex = vao[cell_index * 4 + i];
                vertex.position = sf::Vector2f((x + ((i == 1 || i == 2) ? 1 : 0)) * cell_size,
                    (y + ((i == 2 || i == 3) ? 1 : 0)) * cell_size);
                if (cell.is_alive()) {
                    vertex.color = tribes.at(cell.get_tribe_id()).get_color();
                } else {
                    vertex.color = DEAD_COLOR;
                }
            }
        }
    }

    window.draw(vao);
}

void GameOfLife::click(int x, int y) {
    if (click_kill) {
        get_cell(cells, x, y).die();
    } else {
        get_cell(cells, x, y).live(click_tribe);
    }
}

void GameOfLife::switch_click_tribe() {
    click_tribe++;
    click_tribe %= tribes.size();
}

void GameOfLife::switch_click_kill() {
    click_kill = !click_kill;
}
