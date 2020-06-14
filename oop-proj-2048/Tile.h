#pragma once

#include <cmath>

class Tile {
    int value;
    int hasMerged;
    int xMergedTo;
    int yMergedTo;
    int x;
    int y;

public: 
    Tile();

    Tile(int x, int y, int value);

    int get_value();

    void spawn(int value = 2);

    void reset();

    void remove();

    void mergeWith(Tile& tile);

    int getXMergedTo();

    int getYMergedTo();
 };

