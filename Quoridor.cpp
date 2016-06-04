// Quoridor game for CS159
// Board is 18 x 18 to represent grooves and squares

#include "Quoridor.h"
#include <iterator>
#include <sstream>
#include <vector>
#include <cmath>
#include <queue>
#include <cstring>

using namespace std;

int Quoridor::getTurn() {
  return turn;
}

// gets number of walls on board for current player
int Quoridor::getNumWalls() {

  if (turn == 0)
    return p1->numWalls;
  return p2->numWalls;
}

// TODO: Walls are 0 to 18 (inclusive). Spaces are 1 to 17 (inclusive). Check that there aren't
// off-by-one errors etc.

void Quoridor::makeMove(string action) {
  istringstream iss(action);
  vector<string> move{istream_iterator<string>{iss},
	istream_iterator<string>{}};

  // Either move or build wall.
  if (move.size() == 3 && move[0] == "m") {
    if (isLegalMove(currPlayer(), opposingPlayer(), stoi(move[1]), stoi(move[2]))) {
	updatePlayer(currPlayer(), stoi(move[1]), stoi(move[2]));
	
	// Switch turns.
	turn = (turn + 1) % 2;
    }
    else {
	cout << "Invalid move. Please try again." << endl;
    }
  }
  else if (move.size() == 5 && move[0] == "w") {
    if (isLegalWall(currPlayer(), opposingPlayer(), stoi(move[1]), stoi(move[2]), stoi(move[3]), stoi(move[4]))) {
	updateWall(currPlayer(), stoi(move[1]), stoi(move[2]), stoi(move[3]), stoi(move[4]));
	
	// Switch turns.
	turn = (turn + 1) % 2;
    }
    else {
	cout << "Invalid wall. Please try again." << endl;
    }
  }
  else {
    cout << "Invalid input. Please try again." << endl;
  }
}

bool Quoridor::isWall(int x, int y) {
  return (x % 2)^(y % 2);
}

bool Quoridor::isAlreadyWall(int x, int y) {
  string key = to_string(x) + " " + to_string(y);
  return (walls.find(key) != walls.end());
}

bool Quoridor::onBoard(int x, int y) {
  return (x > 0 && y > 0 && x < 18 && y < 18);
}

vector<string> Quoridor::legalMoves(Player* p1, Player* p2) {
    vector<string> result;
    ostringstream oss;
    // Check legal movement to adjacent spaces, add action if valid
    int x = p1->x;
    int y = p1->y;
    if (isLegalMove(p1, p2, x + 2, y)) {
        oss.str("");
        oss << "m " << x + 2 << " " << y;
        result.push_back(oss.str());
    }
    if (isLegalMove(p1, p2, x - 2, y)) {
        oss.str("");
        oss << "m " << x - 2 << " " << y;
        result.push_back(oss.str());
    }
    if (isLegalMove(p1, p2, x, y + 2)) {
        oss.str("");
        oss << "m " << x << " " << y + 2;
        result.push_back(oss.str());
    }
    if (isLegalMove(p1, p2, x, y - 2)) {
        oss.str("");
        oss << "m " << x << " " << y - 2;
        result.push_back(oss.str());
    }
    return result;
}

vector<string> Quoridor::legalWalls(Player* p1, Player* p2) {
    vector<string> result;
    ostringstream oss;

    if (p1->numWalls == 10) {
        return result;
    }
    
    // This magic denotes the first possible vertical wall
    int sx_start = 1;
    int sy_start = 2;
    int ex_start = 3;
    int ey_start = 2;

    // Check legal wall placements
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // Check vertical walls by iterating through possible positions
            int sx = sx_start + 2 * i;
            int sy = sy_start + 2 * j;
            int ex = ex_start + 2 * i;
            int ey = ey_start + 2 * j;

            // If wall is legal, add action to result
            if (isLegalWall(p1, p2, sx, sy, ex, ey)) {
                oss.str("");
                oss << "w " << sx << " " << sy << " " << ex << " " << ey;
                result.push_back(oss.str());
            }
            // Swap coordinates to check horizontal walls
            sx ^= sy;
            sy ^= sx;
            sx ^= sy;

            ex ^= ey;
            ey ^= ex;
            ex ^= ey;
            // If wall is legal, add action to result
            if (isLegalWall(p1, p2, sx, sy, ex, ey)) {
                oss.str("");
                oss << "w " << sx << " " << sy << " " << ex << " " << ey;
                result.push_back(oss.str());
            }
        }
    }
    return result;
}

// Generates vector of strings that represent possible moves.
// p1: Player whose turn it is
// p2: Other player
// returns: vector of strings (e.g. "m 5 2")
vector<string> Quoridor::getLegalMoves(Player* p1, Player* p2) {
    vector<string> result;
    ostringstream oss;
    // Check legal movement to adjacent spaces, add action if valid
    int x = p1->x;
    int y = p1->y;
    if (isLegalMove(p1, p2, x + 2, y)) {
        oss.str("");
        oss << "m " << x + 2 << " " << y;
        result.push_back(oss.str());
    }
    if (isLegalMove(p1, p2, x - 2, y)) {
        oss.str("");
        oss << "m " << x - 2 << " " << y;
        result.push_back(oss.str());
    }
    if (isLegalMove(p1, p2, x, y + 2)) {
        oss.str("");
        oss << "m " << x << " " << y + 2;
        result.push_back(oss.str());
    }
    if (isLegalMove(p1, p2, x, y - 2)) {
        oss.str("");
        oss << "m " << x << " " << y - 2;
        result.push_back(oss.str());
    }

    if (p1->numWalls == 10) {
        return result;
    }
    
    // This magic denotes the first possible vertical wall
    int sx_start = 1;
    int sy_start = 2;
    int ex_start = 3;
    int ey_start = 2;

    // Check legal wall placements
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // Check vertical walls by iterating through possible positions
            int sx = sx_start + 2 * i;
            int sy = sy_start + 2 * j;
            int ex = ex_start + 2 * i;
            int ey = ey_start + 2 * j;

            // If wall is legal, add action to result
            if (isLegalWall(p1, p2, sx, sy, ex, ey)) {
                oss.str("");
                oss << "w " << sx << " " << sy << " " << ex << " " << ey;
                result.push_back(oss.str());
            }
            // Swap coordinates to check horizontal walls
            sx ^= sy;
            sy ^= sx;
            sx ^= sy;

            ex ^= ey;
            ey ^= ex;
            ex ^= ey;
            // If wall is legal, add action to result
            if (isLegalWall(p1, p2, sx, sy, ex, ey)) {
                oss.str("");
                oss << "w " << sx << " " << sy << " " << ex << " " << ey;
                result.push_back(oss.str());
            }
        }
    }
    return result;
}

    

// Checks if move for player is legal
// Arguments: p1 - current player
//            p2 - opposing player
//            x  - new x position to move to
//            y  - new y position to move to
// TODO: p1 and p2 aren't really necessary.
bool Quoridor::isLegalMove(Player* p1, Player* p2, int x, int y) {
  // New location is off the board
  if (!onBoard(x, y))
    return false;

  // Transform coordinates.
  // int convertX = x * 2 - 1;
  // int y = y * 2 - 1;

  // Check north.
  if (p1->x == x - 2 && p1->y == y && !isAlreadyWall(p1->x - 1, p1->y))
    return true;

  // Check south.
  else if (p1->x == x + 2 && p1->y == y && !isAlreadyWall(p1->x + 1, p1->y))
    return true;

  // Check east.
  else if (p1->x == x && p1->y + 2 == y && !isAlreadyWall(p1->x, p1->y + 1))
    return true;

  // Check west.
  else if (p1->x == x && p1->y - 2 == y && !isAlreadyWall(p1->x, p1->y - 1))
    return true;

  return false;
}

// For the AIs to use
bool Quoridor::checkLegalWall(int sX, int sY, int eX, int eY) {

  return isLegalWall(currPlayer(), opposingPlayer(), sX, sY, eX, eY);
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
    // cout << p1->name << " has no more walls. Enter again." << endl;
    return false;
  }

  // TODO: Check that wall is actually a wall. I.e., not space(s).
  if (!isWall(sX, sY) || !isWall(eX, eY))
    return false;

  // Check wall does not cross boundaries and is not on the edges of the board.
  if (sX == 0 || sY == 0 || eX == 0 || eY == 0 ||
      sX == 18 || sY == 18 || eX == 18 || eY == 18) {
    // cout << "Wall crosses boundaries. Enter again." << endl;
    cout << sX << ", " << sY;
    return false;
  }

  // Check if valid wall. I.e., adjacent edges.
  if (!((sX == eX && abs(sY - eY) == 2) ||
	(abs(sX - eX) && sY == eY))) {
    // cout << "Invalid walls. Enter again." << endl;
    return false;
  }

  // Check that wall does not overlap with existing walls on board
  // TODO: This needs to be more comprehensive. E.g., crossing walls, T-shape.
  if (isAlreadyWall(sX, sY) || isAlreadyWall(eX, eY)) {
    // cout << "Wall already at location. Enter again." << endl;
    return false;
  }
  
  // Check p1.
  if(!floodfill(p1, p2, 17)) {
    // cout << "This wall prevents " << p1->name << " from reaching the end! Enter again." << endl;
    return false;
  }

  // Check p2.
  if(!floodfill(p2, p1, 1)) {
    // cout << "This wall prevents " << p2->name << " from reaching the end! Enter again." << endl;
    return false;
  }

  return true;
}

// Flood fill algorithm to check if there is still a clear end to path
// TODO: p2 added for compatibility with isLegalMove, but not actually needed.
bool Quoridor::floodfill(Player* p1, Player* p2, int end) {
  Player* p = new Player();
  p->x = p1->x;
  p->y = p1->y;

  vector<vector<bool>> visited(18, vector<bool>(18, false));
  queue<pair<int, int>> q;

  // Add player's current position to the queue.
  q.push(make_pair(p1->x, p1->y));

  while (!q.empty()) {
    // Get front of queue and pop off.
    pair<int, int> z = q.front();
    q.pop();

    // Mark as visited.
    visited[z.first][z.second] = true;

    // Update current position.
    p->x = z.first;
    p->y = z.second;

    // Check if opposite side of board has been reached.
    if (z.first == end)
      return true;

    // Check north.
    if (isLegalMove(p, p2, z.first - 2, z.second) && !visited[z.first - 2][z.second]) {
      q.push(make_pair(z.first - 2, z.second));
    }
    
    // Check south.
    if (isLegalMove(p, p2, z.first + 2, z.second) && !visited[z.first + 2][z.second]) {
      q.push(make_pair(z.first + 2, z.second));
    }
    
    // Check east.
    if (isLegalMove(p, p2, z.first, z.second + 2) && !visited[z.first][z.second + 2]) {
      q.push(make_pair(z.first, z.second + 2));
    }
    
    // Check west.
    if (isLegalMove(p, p2, z.first, z.second - 2) && !visited[z.first][z.second - 2]) {
      q.push(make_pair(z.first, z.second - 2));
    }
  }

  return false;
}

// Updates the player's position
void Quoridor::updatePlayer(Player* p, int x, int y) {
  p->x = x;
  p->y = y;
}

// Add another wall
void Quoridor::updateWall(Player* p, int sX, int sY, int eX, int eY) {
  // Insert wall string into set
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

  if (p1->y == 17)
    return 0;

  if (p2->y == 1)
    return 1;

  return -1;
}

// Displays the quoridor board
void Quoridor::displayBoard(ostream& out) {
  out << "    1   2   3   4   5   6   7   8   9" << endl;

  // Edges are even numbers, spaces are odd numbers.
  for (int i=0; i<19; i++) {

    // Vertical numbers.
    if (i % 2 != 0)
      out << i / 2 + 1 << " ";
    else
      out << "  ";

    for (int j=0; j<19; j++) {
        
      if (i % 2 == 0) {
        if (j % 2 == 0) {
	  out << ".";
	  if (j == 18)
	    out << " " << i;
	}
        else {
	  if (isAlreadyWall(i, j))
	    out << " W ";
	  else
	    out << "---";
      }
    }
    else {
      if (j % 2 == 0) {
	if (isAlreadyWall(i, j))
	  out << "W";
	else
	  out << "|";
      }
      else {
        if (p1->x == i && p1->y == j)
          out << " 1 ";
        else if (p2->x == i && p2->y == j)
          out << " 2 ";
        else
          out << "   ";
      }
    }
  }
  out << endl;
  }
  out << "  0   2   4   6   8   10  12  14  16  18" << endl;
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

// Returns a unique string representation of the board as a key for
// the Monte Carlo hash table where
//  - = area taken by wall
//  0 = empty area
//  2 = area taken by player 1
//  3 = area taken by player 2
string Quoridor::boardToStr(Player *p1, Player *p2) {

  char toReturn[325] = {'0'};
  memset(toReturn, '0', sizeof(char) * 324);
  toReturn[324] = 0;
  int arrI = 18 * p1->x + p1->y;
  toReturn[arrI] = '1';
  arrI = 18 * p2->x + p2->y;
  toReturn[arrI] = '2';

  unordered_set<string>::const_iterator curWall;

  for (curWall = walls.begin(); curWall != walls.end(); ++curWall) {
    vector<string> coords = split(*curWall, ' ');
    arrI = 18 * stoi(coords.at(0)) + stoi(coords.at(1));
    toReturn[arrI] = '-';
  }
  ostringstream oss;
  string ret = string(toReturn);
  oss << turn << "," << p1->numWalls << "," << p2->numWalls 
      << ret;

  return oss.str();
}

// Splits a string by the passed in character d
vector<string> Quoridor::split(const string &s, char d) {
    vector<string> v;
    stringstream ss(s);
    string item;
    while (getline(ss, item, d)) {
        v.push_back(item);
    }
    return v;
}

void Quoridor::play() {

  cout << "Welcome to Quoridor!" << endl;
  cout << "m x y: Move to (x, y)" << endl;
  cout << "w xs ys xe ye: Place wall at (xs, ys) and (xe, ye)" << endl << endl;
  string input;
  while (isGameOver() == -1) {
    // Display current board.
    displayBoard(cout);
    
    // Prompt player for move.
    if (!turn)
      cout << endl << p1->name << "> ";
    else
      cout << endl << p2->name << "> ";

    getline(cin, input);
    makeMove(input);
  }

  displayBoard(cout);

  if (isGameOver() == 0)
    cout << p1->name << " has won!" << endl;
  else if (isGameOver() == 1)
    cout << p2->name << " has won!" << endl;
}

void Quoridor::playAI(AI* ai1, AI* ai2, ostream& out) {
  while (isGameOver() == -1) {
    ai1->q = this;
    ai2->q = this;

    out << "Player 1: " << p1->x << " " << p1->y << endl;
    out << "Player 2: " << p2->x << " " << p2->y << endl;

    // Display current board.
    displayBoard(out);

    string move;
    
    // Prompt player for move.
    if (!turn) {
      move = ai1->getNextMove();
      out << "AI 1: " << move << endl;
    }
    else {
      move = ai2->getNextMove();
      out << endl << "AI 2: " << move << endl;
    }

    makeMove(move);
    // break;
  }

  displayBoard(out);

  if (isGameOver() == 0)
    out << p1->name << " has won!" << endl;
  else if (isGameOver() == 1)
    out << p2->name << " has won!" << endl;
}

