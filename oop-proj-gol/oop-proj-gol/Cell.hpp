#pragma once

#include <stdexcept>

class Cell
{
private:
    int tribe_id;
    bool alive;
public:
    Cell();

    int get_tribe_id() const;

    int is_alive() const;

    void live(int tribe_id);

    void die();
};