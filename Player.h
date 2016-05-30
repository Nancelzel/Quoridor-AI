#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>

// Represents a player
struct Player {
  // Name of player
  std::string name;

  // Current x coordinate
  double x;

  // Current y coordinate
  double y;

  // Number of walls player has left
  int numWalls;
};

#endif
