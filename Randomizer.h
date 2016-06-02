#ifndef RANDOMIZER_H_
#define RANDOMIZER_H_

#include "Quoridor.h"
#include <string>

// Returns the next move Randomizer decides to make to Quoridor
std::string getNextMove(Quoridor q);

// randomly decides to move or place a wall
int moveOrWall(Quoridor q);

#endif
