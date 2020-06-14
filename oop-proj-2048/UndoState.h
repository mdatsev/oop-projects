#pragma once

#include <vector>
#include "Tile.h"

struct UndoState {
    std::vector<std::vector<Tile>> tiles;
    unsigned long seed;
    int score;
};

