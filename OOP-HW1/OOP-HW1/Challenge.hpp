#pragma once

#include <iomanip>
#include "string.hpp"

class Challenge
{
public:
    string tag;
    int times_challenged = 0;
    int times_finished = 0;
    float score = 0;

    Challenge(string tag = {});

    void finish(float rating);

    void challenge();

};

std::ostream& operator<<(std::ostream& output, Challenge& s);