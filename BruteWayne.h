#ifndef BRUTE_WAYNE_H_
#define BRUTE_WAYNE_H_

#include "Quoridor.h"

typedef std::pair<std::pair<int, int>, double> Node;

class BruteWayne {
  // Returns the next move Randomizer decides to make to Quoridor
  std::string getNextMove();

  // Randomly decides to move or place a wall
  int moveOrWall();

  Quoridor q;

};

#endif
