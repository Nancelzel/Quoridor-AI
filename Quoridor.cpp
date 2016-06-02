// Quoridor game for CS159
// Board is 18 x 18 to represent grooves and squares

#include "Quoridor.h"
#include <iterator>
#include <sstream>
#include <vector>
#include <cmath>
#include <unordered_map>

using namespace std;

// std::unordered_map<int, char> intToChar ({{0, 'A'}, {2, 'B'}, {4, 'C'}, {6, 'D'}, {8, 'E'}, {10, 'F'}, {12, 'G'}, {14, 'H'}, {16, 'I'}, {18, 'J'}});
// std::unordered_map<int, char> charToInt ({{'A', 0}, {'B', 2}, {'C', 4}, {'D', 6}, {'E', 8}, {'F', 10}, {'G', 12}, {'H', 14}, {'I', 16}, {'J', 18}});

/*
// Gets the integer corresponding to the letter.
int getInt(char letter) {
  return (int)letter;
}

// Gets the letter corresponding to the integer.
char getLetter(int number) {
  // return number - 87;
  return '0' + number;
}
*/

// Checks if move for player is legal
// Arguments: p1 - current player
//            p2 - opposing player
//            x  - new x position to move to
//            y  - new y position to move to
bool Quoridor::isLegalMove(Player* p1, Player* p2, int x, int y) {
  // New location is off the board
  if (x < 0 || y < 0 || x > bound || y > bound) {
    cout << "Out of bounds. Enter again." << endl;
    return false;
  }

  // New location is occupied by another player
  if (p2->x == x && p2->y == y) {
    cout << "Location occupied by another player. Enter again." << endl;
    return false;
  }

  int convertX = x * 2 - 1;
  int convertY = y * 2 - 1;

  int xDist = abs(p1->x - convertX);
  int yDist = abs(p1->y - convertY);

  cout << xDist << " " << yDist << endl;

  // New location is not adjacent/orthogonal to player
  if (xDist > 2 || yDist > 2) {

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

    cout << "Invalid move. Enter again." << endl;

    return false;
  }

  return true;
}

// Checks if the wall placed is legal
// Arguments: p1  - current player placing the wall
//            p2  - opposing player
//            sX  - start x position for wall
//            sY  - start y position for wall
//            eX  - end x position for wall
//            eY  - end y position for wall
bool Quoridor::isLegalWall(Player* p1, Player* p2, int sX, int sY, int eX, int eY) {

  // Check player still has wall to put down
  if (p1->numWalls == 10) {
    cout << p1->name << " has no more walls. Enter again." << endl;
    return false;
  }

  // Check wall does not cross boundaries
  if (sX < 0 || sY < 0 || eX < 0 || eY < 0 || sX > bound || sY > bound) {
    cout << "Wall crosses boundaries. Enter again." << endl;
    return false;
  }

  // Check that wall is not at the boundaries

  // Check that wall does not overlap with existing walls on board

  vector<Coordinate*> visited;
  Coordinate* curSpace;
  curSpace->x = p1->x;
  curSpace->y = p1->y;

  // Use floodfill algorithm to determine if a path is still reachable after adding wall for
  // current player.
  if(!floodfill(visited, curSpace)) {
    cout << "This wall prevents " << p1->name << " from reaching the end! Enter again." << endl;
    return false;
  }

  visited.clear();
  curSpace->x = p2->x;
  curSpace->y = p2->y;

  if(!floodfill(visited, curSpace)) {
    cout << "This wall prevents " << p2->name << " from reaching the end! Enter again." << endl;
    return false;
  }

  return true;
}

// Flood fill algorithm to check if there is still a clear end to path
bool Quoridor::floodfill(vector<Coordinate*> visited, Coordinate* curSpace) {

  // Check if current space overlaps with a wall
  for (int i=0; i<numWalls; i++) {
    Wall curWall = walls[i];

    if ((curSpace->x == curWall.sX && curSpace->y == curWall.sY) ||
        (curSpace->x == curWall.mX && curSpace->y == curWall.mY) ||
        (curSpace->x == curWall.eX && curSpace->y == curWall.eY))
      return false;
  }

  // Check if end goal is reached; if not check adjacent spaces
  if (turn == 0 && curSpace->y == 17)
    return true;
  else if (turn == 1 && curSpace->y == 1)
    return true;
  else {
    visited.push_back(curSpace);
    Coordinate* nextSpace;
    nextSpace->x = curSpace->x + 2;
    nextSpace->y = curSpace->y;
    bool east = floodfill(visited, nextSpace);
    nextSpace->x = curSpace->x - 2;
    nextSpace->y = curSpace->y;
    bool west = floodfill(visited, nextSpace);
    nextSpace->x = curSpace->x;
    nextSpace->y = curSpace->y + 2;
    bool north = floodfill(visited, nextSpace);
    nextSpace->x = curSpace->x;
    nextSpace->y = curSpace->y - 2;
    bool south = floodfill(visited, nextSpace);

    if (east || west || north || south)
      return true;

    return false;
  }
}

// Updates the player's position
void Quoridor::updatePlayer(Player* p, int x, int y) {

  p->x = 2 * x - 1;
  p->y = 2 * y - 1;
}

// Add another wall
void Quoridor::updateWall(Player* p, int sX, int sY, int eX, int eY) {

  Wall w;
  w.sX = sX;
  w.sY = sY;
  w.eX = eX;
  w.eY = eY;

  if (sX == eX) {
    w.mX = sX;

    if (sY < eY)
      w.mY = sY + 1;
    else
      w.mY = sY - 1;
  }
  else {
    w.mY = sY;

    if (sX < eX)
      w.mX = sX + 1;
    else
      w.mY = sX - 1;
  }

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
        if (j % 2 == 0) {
	  cout << ".";
	  if (j == 18)
	    cout << " " << i;
	}
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
        else if (p2->x == i && p2->y == j)
          cout << " 2 ";
        else
          cout << "   ";
      }
    }
  }
  cout << endl;
  }
  cout << "  0   2   4   6   8   10  12  14  16  18" << endl;
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
  cout << "w xs ys xe ye: Place wall at (xs, ys) and (xe, ye)" << endl << endl;
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
      if (isLegalWall(currPlayer(), opposingPlayer(), stoi(move[1]), stoi(move[2]), stoi(move[3]), stoi(move[4]))) {
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

