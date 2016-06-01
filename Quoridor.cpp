// Quoridor game for CS159
// Board is 18 x 18 to represent grooves and squares

#include "Quoridor.h"
#include <iterator>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

// Checks if move for player is legal
// Arguments: p1 - current player
//            p2 - opposing player
//            x  - new x position to move to
//            y  - new y position to move to
bool Quoridor::isLegalMove(Player* p1, Player* p2, int x, int y) {
  // New location is off the board
  if (x < 0 || y < 0 || x > bound || y > bound) {
    cout << "Out of bounds. Please choose another location." << endl;
    return false;
  }

  // New location is occupied by another player
  if (p2->x == x && p2->y == y) {
    cout << "Location occupied by another player. Please choose another location." << endl;
    return false;
  }

  int convertX = x * 2 - 1;
  int convertY = y * 2 - 1;

  int xDist = abs(p1->x - convertX);
  int yDist = abs(p1->y - convertY);

  // New location is not adjacent/orthogonal to player
  if ((xDist > 2 && yDist == 0) || (xDist == 0 && yDist > 2)) {

    // Other player is in front of current player
    if (p2->x - 2 == p1->x && p2->y == p1->y) {

      // New location is walled
      for (int i=0; i<numWalls; i++) {
        Wall curWall = walls[i];

        if ((curWall.sX - 1 == p2->x && curWall.eX - 1 == p2->x) &&
           ((curWall.sY + 1 == p2->y && curWall.eY - 1 == p2->y) ||
            (curWall.sY - 1 == p2->y && curWall.eY + 1 == p2->y))) {
          if ((p1->x + 2 == convertX && p1->y + 2 == convertY) ||
              (p1->x + 2 == convertX && p1->y - 2 == convertY))
            return true;
        }
      }

      // New location is a jump forward
      if (p1->x + 4 == convertX && p1->y == convertY)
        return true;
    }

    // Other player is behind current player
    if (p2->x + 2 == p1->x && p2->y == p1->y) {

      // New location is walled
      for (int i=0; i<numWalls; i++) {
        Wall curWall = walls[i];

        if ((curWall.sX + 1 == p2->x && curWall.eX + 1 == p2->x) &&
           ((curWall.sY + 1 == p2->y && curWall.eY - 1 == p2->y) ||
            (curWall.sY - 1 == p2->y && curWall.eY + 1 == p2->y))) {
          if ((p1->x - 2 == convertX && p1->y + 2 == convertY) ||
              (p1->x - 2 == convertX && p1->y - 2 == convertY))
            return true;
        }
      }

      // New location is a jump backwards
      if (p1->x - 4 == convertX && p1->y == convertY)
        return true;
    }

    // Other player is above current player
    if (p2->x == p1->x && p2->y + 2 == p1->y) {

      // New location is walled
      for (int i=0; i<numWalls; i++) {
        Wall curWall = walls[i];

        if ((curWall.sY + 1 == p2->y && curWall.eY + 1 == p2->y) &&
           ((curWall.sX + 1 == p2->x && curWall.eX - 1 == p2->x) ||
            (curWall.sX - 1 == p2->x && curWall.eX + 1 == p2->x))) {
          if ((p1->x - 2 == convertX && p1->y + 2 == convertY) ||
              (p1->x - 2 == convertX && p1->y - 2 == convertY))
            return true;
        }
      }

      // New location is a jump upwards
      if (p1->x == convertX && p1->y - 4 == convertY)
        return true;
    }

    // Other player is below current player
    if (p2->x == p1->x && p2->y - 2 == p1->y) {

      // New location is walled
      for (int i=0; i<numWalls; i++) {
        Wall curWall = walls[i];

        if ((curWall.sY - 1 == p2->y && curWall.eY - 1 == p2->y) &&
           ((curWall.sX + 1 == p2->x && curWall.eX - 1 == p2->x) ||
            (curWall.sX - 1 == p2->x && curWall.eX + 1 == p2->x))) {
          if ((p1->x - 2 == convertX && p1->y + 2 == convertY) ||
              (p1->x - 2 == convertX && p1->y - 2 == convertY))
            return true;
        }
      }

      // New location is a jump downwards
      if (p1->x == convertX && p1->y + 4 == convertY)
        return true;
    }

    cout << "Invalid move. Please choose another location." << endl;

    return false;
  }

  return true;
}

// Checks if the wall placed is legal
bool Quoridor::isLegalWall(Player* p, int sX, int sY, int eX, int eY) {
  if (p->numWalls == 10) {
    cout << p->name << " has no more walls." << endl;
    return false;
  }

  // Use floodfill algorithm
  return true;
}

// Updates the player's position
void Quoridor::updatePlayer(Player* p, int x, int y) {
  p->x = 2 * x - 1;
  p->y = 2 * y - 1;
  return;
}

// Add another wall
void Quoridor::updateWall(Player* p, int sX, int sY, int eX, int eY) {

  Wall w;
  w.sX = sX;
  w.sY = sY;
  w.eX = eX;
  w. eY = eY;

  walls[numWalls] = w;
  numWalls++;
  p->numWalls++;
}

// Checks if current player has won
// Returns: -1 if no player has won
//           0 if player 1 has won
//           1 if player 2 has won
int Quoridor::isGameOver() {

  if (p1->x == 17)
    return 0;

  if (p2->x == 1)
    return 1;

  return -1;
}

// Displays the quoridor board
void Quoridor::displayBoard() {
  cout << "    1   2   3   4   5   6   7   8   9" << endl;

  // Edges are even numbers, spaces are odd numbers.
  for (int i=0; i<19; i++) {

    // Vertical numbers.
    if (i % 2 != 0)
      cout << i / 2 + 1 << " ";
    else
      cout << "  ";

    for (int j=0; j<19; j++) {
        
      if (i % 2 == 0) {
	if (j % 2 == 0)
	  cout << ".";
	else {
	  bool wall = false;
	  for (int k = 0; k < numWalls; ++k) {
	    if ((walls[k].sX == i && walls[k].sY == j) ||
		(walls[k].eX == i && walls[k].eY == j)) {
	      cout << " W ";
	      wall = true;
	      break;
	    } 
	  }
	  if (!wall)
	    cout << "---";
	}
      }
      else {
	if (j % 2 == 0) {
	  bool wall = false;
	  for (int k = 0; k < numWalls; ++k) {
	    if ((walls[k].sX == i && walls[k].sY == j) ||
		(walls[k].eX == i && walls[k].eY == j)) {
	      cout << "W";
	      wall = true;
	      break;
	    } 
	  }
	  if (!wall)
	    cout << "|";
	}
	else {
	  if (p1->x == i && p1->y == j)
	    cout << " 1 ";
	  else if (p2->x == i && p1->y == j)
	    cout << " 2 ";
	  else
	    cout << "   ";
	}
      }
    }

    cout << endl;
  }
}

Player* Quoridor::currPlayer() {
  if (turn == 0)
    return p1;
  return p2;
}

Player* Quoridor::opposingPlayer() {
  if (turn == 0)
    return p2;
  return p1;
}

void Quoridor::play() {
  cout << "Welcome to Quoridor!" << endl;
  cout << "m x y: Move to (x, y)" << endl;
  cout << "w xs ys xe ye: Place wall from (xs, ys) to (xe, ye)" << endl << endl;
  string input;
  while (isGameOver() == -1) {
    // Display current board.
    displayBoard();
    
    // Prompt player for move.
    if (!turn)
      cout << endl << p1->name << "> ";
    else
      cout << endl << p2->name << "> ";

    getline(cin, input);
    istringstream iss(input);
    vector<string> move{istream_iterator<string>{iss},
	istream_iterator<string>{}};

    // Either move or build wall.
    if (move.size() == 3 && move[0] == "m") {
      if (isLegalMove(currPlayer(), opposingPlayer(), stoi(move[1]), stoi(move[2]))) {
	updatePlayer(currPlayer(), stoi(move[1]), stoi(move[2]));
	
	// Switch turns.
	turn = (turn + 1) % 2;
      }
    }
    else if (move.size() == 5 && move[0] == "w") {
      if (isLegalWall(currPlayer(), stoi(move[1]), stoi(move[2]), stoi(move[3]), stoi(move[4]))) {
	updateWall(currPlayer(), stoi(move[1]), stoi(move[2]), stoi(move[3]), stoi(move[4]));
	
	// Switch turns.
	turn = (turn + 1) % 2;
      }
    }
    else {
      cout << "Invalid move. Please try again." << endl;
    }
  }

  if (isGameOver() == 0)
    cout << p1->name << " has won!" << endl;
  else if (isGameOver() == 1)
    cout << p2->name << " has won!" << endl;
}

