// copied from https://stackoverflow.com/a/10198842/9156061

#include "LCG.h"

#include <ctime>

LCG randomGenerator(std::time(NULL));

LCG::LCG(unsigned long seed) : next(seed) {}

int LCG::rand() {
    next = next * 1103515245 + 12345;
    return (unsigned int)(next / 65536) % 32768;
}

void LCG::setSeed(unsigned long seed) {
    next = seed;
}

unsigned long LCG::getSeed() {
    return next;
}
