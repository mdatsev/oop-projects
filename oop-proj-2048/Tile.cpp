#include "Tile.h"

Tile::Tile() {

}

Tile::Tile(int x, int y, int value) : x(x), y(y), value(value) {
    reset();
}

int Tile::get_value() {
    return value;
}

void Tile::spawn(int value) {
    this->value = value;
}

void Tile::reset() {
    hasMerged = false;
    xMergedTo = x;
    yMergedTo = y;
}

void Tile::remove() {
    value = 0;
}

void Tile::mergeWith(Tile& tile) {
    if (value != 0) {
        if (hasMerged) {
            return;
        } else {
            hasMerged = true;
        }
    }

    value += tile.value;
    tile.value = 0;

    tile.xMergedTo = x;
    tile.yMergedTo = y;
}

int Tile::getXMergedTo() {
    return xMergedTo;
}

int Tile::getYMergedTo() {
    return yMergedTo;
}
