#include "Cell.hpp"

int Cell::get_tribe_id() const {
    if (!alive) {
        throw std::logic_error("Dead cell has no tribe");
    }
    return tribe_id;
}

int Cell::is_alive() const {
    return alive;
}

void Cell::live(int tribe_id) {
    this->tribe_id = tribe_id;
    alive = true;
}

void Cell::die() {
    alive = false;
}

Cell::Cell() : alive{ false }, tribe_id{ -1 } {

}