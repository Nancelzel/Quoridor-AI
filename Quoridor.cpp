// Quoridor game for CS159
// Board is 18 x 18 to represent grooves and squares

#include "Quoridor.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Checks if move for player is legal
// Arguments: p1 - current player
//            p2 - opposing player
//            x  - new x position to move to
//            y  - new y position to move to
bool Quoridor::isLegalMove(Player p1, Player p2, double x, double y) {

  // New location is off the board
  if (x < 0 || y < 0 || x > bound || y > bound) {
    cout << "Out of bounds." << endl;
    return false;
  }

  // New location is occupied by another player
  if (p2.x == x && p2.y == y) {
    cout << "Location occupied by another player." << endl;
    return false;
  }

  double convertX = x * 2 - 1;
  double convertY = y * 2 - 1;

  double xDist = abs(p1.x - convertX);
  double yDist = abs(p1.y - convertY);

  // New location is not adjacent/orthogonal to player
  if ((xDist > 2 && yDist == 0) || (xDist == 0 && yDist > 2)) {

    // Other player is in front of current player
    if (p2.x - 2 == p1.x && p2.y == p1.y) {

      // New location is walled
      for (int i=0; i<numWalls; i++) {
	Wall curWall = walls[i];

	if ((curWall.sX - 1 == p2.x && curWall.eX - 1 == p2.x) &&
	    ((curWall.sY + 1 == p2.y && curWall.eY - 1 == p2.y) || (curWall.sY - 1 == p2.y && curWall.eY + 1 == p2.y))) {
	  if ((p1.x + 2 == convertX && p1.y + 2 == convertY) || (p1.x + 2 == convertX && p1.y - 2 == convertY))
	    return true;
	}
      }

      // New location is a jump forward
      if (p1.x + 4 == convertX && p1.y == convertY)
	return true;
    }

    // Other player is behind current player
    if (p2.x + 2 == p1.x && p2.y == p1.y) {

      // New location is walled
      for (int i=0; i<numWalls; i++) {
	Wall curWall = walls[i];

	if ((curWall.sX + 1 == p2.x && curWall.eX + 1 == p2.x) &&
	    ((curWall.sY + 1 == p2.y && curWall.eY - 1 == p2.y)|| (curWall.sY - 1 == p2.y && curWall.eY + 1 == p2.y))) {
	  if ((p1.x - 2 == convertX && p1.y + 2 == convertY) || (p1.x - 2 == convertX && p1.y - 2 == convertY))
	    return true;
	}
      }

      // New location is a jump backwards
      if (p1.x - 4 == convertX && p1.y == convertY)
	return true;
    }

    // Other player is above current player
    if (p2.x == p1.x && p2.y + 2 == p1.y) {

      // New location is walled
      for (int i=0; i<numWalls; i++) {
	Wall curWall = walls[i];

	if ((curWall.sY + 1 == p2.y && curWall.eY + 1 == p2.y) &&
	    (curWall.sX + 1 == p2.x && curWall.eX - 1 == p2.x) || (curWall.sX - 1 == p2.x && curWall.eX + 1 == p2.x)) {
	  if ((p1.x - 2 == convertX && p1.y + 2 == convertY) || (p1.x - 2 == convertX && p1.y - 2 == convertY))
	    return true;
	}
      }

      // New location is a jump upwards
      if (p1.x == convertX && p1.y - 4 == convertY)
	return true;
    }

    // Other player is below current player
    if (p2.x == p1.x && p2.y - 2 == p1.y) {

      // New location is walled
      for (int i=0; i<numWalls; i++) {
	Wall curWall = walls[i];

	if ((curWall.sY - 1 == p2.y && curWall.eY - 1 == p2.y) &&
	    (curWall.sX + 1 == p2.x && curWall.eX - 1 == p2.x) || (curWall.sX - 1 == p2.x && curWall.eX + 1 == p2.x)) {
	  if ((p1.x - 2 == convertX && p1.y + 2 == convertY) || (p1.x - 2 == convertX && p1.y - 2 == convertY))
	    return true;
	}
      }

      // New location is a jump downwards
      if (p1.x == convertX && p1.y + 4 == convertY)
	return true;
    }

    cout << "Invalid move." << endl;

    return false;
  }

  return true;
}

// Checks if the wall placed is legal
bool Quoridor::isLegalWall(Player p) {

  if (p.numWalls < 20) {
    cout << p.name << " has no more walls." << endl;
    return false;
  }

  // Use floodfill algorithm
    
  return true;
}

// Updates the current player's position
void Quoridor::updatePlayer(Player p1, Player p2, int x, int y) {

  p1.x = x;
  p1.y = y;

  // Switch to other player's turn
  turn = (turn + 1) % 2;
}

// Add another wall
void Quoridor::updateWall(int sX, int sY, int eX, int eY) {

  Wall w;
  w.sX = sX;
  w.sY = sY;
  w.eX = eX;
  w. eY = eY;

  walls[numWalls] = w;
  numWalls++;

  // Switch to other player's turn
  turn = (turn + 1) % 2;
}

// Checks if current player has won
// Returns: -1 if no player has won
//           0 if player 1 has won
//           1 if player 2 has won
int Quoridor::isGameOver(Player p) {

  // 1st player reached end
  if (turn == 0) {
    if(p.x == 17)
      return 0;
  }

  // 2nd player reached end
  if (turn == 1) {
    if(p.x == 1)
      return 1;
  }

  return -1;
}

// Displays the quoridor board
void Quoridor::displayBoard() {

  cout << "   1  2  3  4  5  6  7  8  9" << endl;

  for (int i=0; i<19; i++) {

    if (i % 2 != 0)
      cout << i / 2 + 1 << " ";
    else
      cout << "  ";

    for (int j=0; j<19; j++) {
        
      if (i % 2 == 0) {
	if (j % 2 == 0)
	  cout << ".";
	else
	  cout << "--";
      }
      else {
	if (j % 2 == 0)
	  cout << "|";
	else
	  cout << "  ";
      }
    }

    cout << endl;
  }
}

