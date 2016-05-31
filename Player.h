#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>

// Represents a player
struct Player {
  // Name of player
  std::string name;

  // Current x coordinate
  int x;

  // Current y coordinate
  int y;

  // Number of walls player has on the board
  int numWalls;
};

#endif
