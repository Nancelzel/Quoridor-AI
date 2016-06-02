// Random AI to play Quoridor

#include "Randomizer.h"
#include "Quoridor.h"
#include <string>
#include <stdlib.h>

using namespace std;

// Returns the next move Randomizer decides to make to Quoridor
String getNextMove() {

  String toReturn = "";

  if (moveOrWall() == 0) {
    toReturn += "m ";
    vector<string> legalMoves = getLegalMoves();

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

    while(!checkLegalWall(sX, sY, eX, eY)) { 
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

    toReturn += sX + " " + sY + " " + eX + " " + eY;
  }

  return toReturn;
}

// randomly decides to move or place a wall
// Returns: 0 - move
//          1 - place a wall
int moveOrWall() {
  
  // AI has no more walls to place down, will strictly move
  if(getNumWalls() == 10)
    return 0;

  return rand() % 2;
};