// Random AI to play Quoridor

#include "Randomizer.h"
// #include "Quoridor.h"
// #include <string>
#include <stdlib.h>

using namespace std;

// Returns the next move Randomizer decides to make to Quoridor
string Randomizer::getNextMove() {

  string toReturn = "";

  if (moveOrWall() == 0) {
    toReturn += "m ";
    vector<string> legalMoves = q.getLegalMoves(q.currPlayer(), q.opposingPlayer());

    int randMove = rand() % legalMoves.size();

    toReturn += legalMoves.at(randMove);
  }
  else {
    toReturn += "w ";

    // Keep generating random walls until it's legal
    int sX = 0;
    int sY = 0;
    int eX = 0;
    int eY = 0;

    while(!q.checkLegalWall(sX, sY, eX, eY)) { 
      Wall w;
      sX = rand() % 17 + 1;
      sY = rand() % 17 + 1;
      int dir = rand() % 4;  // 0: N; 1: S; 2: E; 3: W

      switch(dir) {
        case 0:
          eX = w.sX - 2;
          eY = w.sY;
          break;
        case 1:
          eX = w.sX + 2;
          eY = w.sY;
          break;
        case 2:
          eX = w.sX;
          eY = w.sY + 2;
          break;
        default:
          eX = w.sX;
          eY = w.sY - 2;
      }
    }

    toReturn += to_string(sX) + " " + to_string(sY) + " " + to_string(eX) + " " + to_string(eY);
  }

  return toReturn;
}

// randomly decides to move or place a wall
// Returns: 0 - move
//          1 - place a wall
int Randomizer::moveOrWall() {
  
  // AI has no more walls to place down, will strictly move
  if(q.getNumWalls() == 10)
    return 0;

  return rand() % 2;
};
