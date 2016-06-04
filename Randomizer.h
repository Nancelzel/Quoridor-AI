#ifndef RANDOMIZER_H_
#define RANDOMIZER_H_

#include "AI.h"
#include <string>

class Randomizer : public AI {
  // Returns the next move Randomizer decides to make to Quoridor
  std::string getNextMove();

  // Randomly decides to move or place a wall
  int moveOrWall();
};

#endif
