#pragma once

class LCG {
private:
    unsigned long next = 1;
public:

    LCG(unsigned long seed);

    static const unsigned long rand_max = 32767;

    int rand();

    void setSeed(unsigned long seed);

    unsigned long getSeed();
};


extern LCG randomGenerator;

