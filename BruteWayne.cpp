#include "BruteWayne.h"
#include <string>

std::string BruteWayne::getNextMove() {
  return "TODO: implement this";
  // Choose whether to move or wall.
  // If move, use Dijkstra's algorithm.
  // If wall, choose a random wall.
}

int BruteWayne::moveOrWall() {
  // AI has no more walls to place down, will strictly move
  if(q.getNumWalls() == 10)
    return 0;

  return rand() % 2;
}
