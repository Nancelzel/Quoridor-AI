// Random AI to play Quoridor

#include "Randomizer.h"
// #include "Quoridor.h"
// #include <string>
#include <algorithm>
#include <stdlib.h>

using namespace std;

// Returns the next move Randomizer decides to make to Quoridor
string Randomizer::getNextMove() {
  if (moveOrWall() == 1) {
    std::vector<std::string> possible_walls = q->legalWalls(q->currPlayer(), q->opposingPlayer());
    std::random_shuffle(possible_walls.begin(), possible_walls.end());
    return possible_walls[0];
  }

  std::vector<std::string> possible_moves = q->legalMoves(q->currPlayer(), q->opposingPlayer());
  std::random_shuffle(possible_moves.begin(), possible_moves.end());
  return possible_moves[0];
}

// randomly decides to move or place a wall
// Returns: 0 - move
//          1 - place a wall
int Randomizer::moveOrWall() {
  
  // AI has no more walls to place down, will strictly move
  if(q->getNumWalls() == 10)
    return 0;

  return rand() % 2;
};
