// Quoridor game for CS159
// Board is 18 x 18 to represent grooves and squares

#include "Quoridor.h"
#include <iterator>
#include <sstream>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

bool Quoridor::isWall(int x, int y) {
  string key = to_string(x) + " " + to_string(y);
  return (walls.find(key) != walls.end());
}

bool Quoridor::onBoard(int x, int y) {
  return (x < 0 && y < 0 && x > bound && y > bound);
}

// Checks if move for player is legal
// Arguments: p1 - current player
//            p2 - opposing player
//            x  - new x position to move to
//            y  - new y position to move to
// TODO: p1 and p2 aren't really necessary.
bool Quoridor::isLegalMove(Player* p1, Player* p2, int x, int y) {
  // New location is off the board
  if (!onBoard(x, y)) {
    cout << "Out of bounds. Enter again." << endl;
    return false;
  }

  // Transform coordinates.
  int convertX = x * 2 - 1;
  int convertY = y * 2 - 1;

  // Check north.
  // TODO: Check walls.
  if (p1->x == convertX && p1->y - 1 == convertY)
    return true;

  // Check south.
  else if (p1->x == convertX && p1->y + 1 == convertY)
    return true;

  // Check east.
  else if (p1->x + 1 == convertX && p1->y == convertY)
    return true;

  // Check west.
  else if (p1->x - 1 == convertX && p1->y == convertY)
    return true;

  return false;
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

  // Check wall does not cross boundaries and is not on the edges of the board.
  if (sX < 2 || sY < 2 || eX < 2 || eY < 2 ||
      sX > 16 || sY > 16 || eX > 16 || eY > 16) {
    cout << "Wall crosses boundaries. Enter again." << endl;
    return false;
  }

  // Check if valid wall. I.e., adjacent edges.
  if (!((sX == eX && abs(sY - eY) == 2) ||
	(abs(sX - eX) && sY == eY))) {
    cout << "Invalid walls. Enter again." << endl;
  }

  // Check that wall does not overlap with existing walls on board
  if (isWall(sX, sY) || isWall(eX, eY))
    cout << "Wall already at location. Enter again." << endl;
  
  // Check p1.
  if(!floodfill(p1, 17)) {
    cout << "This wall prevents " << p1->name << " from reaching the end! Enter again." << endl;
    return false;
  }

  // Check p2.
  if(!floodfill(p2, 1)) {
    cout << "This wall prevents " << p2->name << " from reaching the end! Enter again." << endl;
    return false;
  }

  return true;
}

// Flood fill algorithm to check if there is still a clear end to path
// bool Quoridor::floodfill(vector<Coordinate*> visited, Coordinate* curSpace) {
bool Quoridor::floodfill(Player* p, int end) {
  vector<vector<bool>> visited(18, vector<bool>(18, false));
  queue<pair<int, int>> q;

  // Add player's current position to the queue.
  q.push(make_pair(p->x, p->y));
  visited[p->x][p->y] = true;

  while (!q.empty()) {
    // Get front of queue and pop off.
    pair<int, int> z = q.front();
    q.pop();

    // Check if opposite side of board has been reached.
    if (z.first == end)
      return true;

    // Check north.
    // TODO: add isLegalMove stipulation.
    if (!isWall(z.first, z.second - 1) && !visited[z.first][z.second - 1]) {
      q.push(make_pair(z.first, z.second - 1));
      visited[z.first][z.second - 1] = true;
    }
    
    // Check south.
    if (!isWall(z.first, z.second + 1) && !visited[z.first][z.second + 1]) {
      q.push(make_pair(z.first, z.second + 1));
      visited[z.first][z.second + 1] = true;
    }
    
    // Check east.
    if (!isWall(z.first + 1, z.second) && !visited[z.first + 1][z.second]) {
      q.push(make_pair(z.first + 1, z.second));
      visited[z.first + 1][z.second] = true;
    }
    
    // Check west.
    if (!isWall(z.first - 1, z.second) && !visited[z.first - 1][z.second]) {
      q.push(make_pair(z.first - 1, z.second));
      visited[z.first - 1][z.second] = true;
    }
  }

  return false;
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

  walls.insert(to_string(sX) + " " + to_string(sY));
  walls.insert(to_string(eX) + " " + to_string(eY));
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
	  if (isWall(i, j))
	    cout << " W ";
	  else
	    cout << "---";
      }
    }
    else {
      if (j % 2 == 0) {
	if (isWall(i, j))
	  cout << "W";
	else
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

