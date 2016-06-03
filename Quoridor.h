#ifndef QUORIDOR_H_
#define QUORIDOR_H_

#include "Player.h"
#include "Wall.h"
#include "AI.h"

#include <iostream>
#include <utility>
// #include <ostream>
#include <vector>
#include <unordered_set>

class AI;

class Quoridor {
 public:
  // Constructor
  Quoridor() {
    // Player 1 starts at the left side of board
    p1 = new Player();
    p1->name = "Player 1";
    p1->x = 9;
    p1->y = 1;
    p1->numWalls = 0;

    // Player 2 starts at the right side of board
    p2 = new Player();
    p2->name = "Player 2";
    p2->x = 9;
    p2->y = 17;
    p2->numWalls = 0;
    
    // Start with player 1
    turn = 0;
    numWalls = 0;
    bound = 9;
  }

  Quoridor(const Quoridor &q) {
    p1 = new Player(*q.p1);
    p2 = new Player(*q.p2);
    turn = q.turn;
    walls = std::unordered_set<std::string>(q.walls);
    numWalls = q.numWalls;
    bound = q.bound;
  }



  // Makes a move on a board
  void makeMove(std::string action);

  // gets the number of walls on board for current player
  int getNumWalls();

  int getTurn();

  // Checks if this is a wall (as opposed to a space).
  bool isWall(int x, int y);

  // Checks if there is a wall at (x, y).
  bool isAlreadyWall(int x, int y);

  // Checks if the given space is on the board.
  bool onBoard(int x, int y);

  std::vector<std::string> legalMoves(Player* p1, Player* p2);
  std::vector<std::string> legalWalls(Player* p1, Player* p2);
  std::vector<std::string> getLegalMoves(Player* p1, Player* p2);

  // Checks if player move is legal
  bool isLegalMove(Player* p1, Player* p2, int x, int y);
  // bool isLegalMove(Player* p1, Player* p2, std::string move);

  // For the AIs to use
  bool checkLegalWall(int sX, int sY, int eX, int eY);

  // Checks if wall placed is legal
  bool isLegalWall(Player* p1, Player* p2, int sX, int sY, int eX, int eY);

  // Updates player's position
  void updatePlayer(Player* p, int x, int y);

  // Add a wall on the board
  void updateWall(Player* p, int sX, int sY, int eX, int eY);

  // Flood fill algorithm to check if there is still a clear end to path
  bool floodfill(Player* p1, Player* p2, int end);

  // Checks if a player has won
  int isGameOver();

  // Displays the board
  void displayBoard(std::ostream& out);

  // Play a game of Quoridor.
  void play();

  void playAI(AI* ai1, AI* ai2, std::ostream& out);

  // Returns the current player
  Player* currPlayer();

  // Returns the opposing player
  Player* opposingPlayer();

  // Returns a unique string representation of the board as a key for
  // the Monte Carlo hash table
  std::string boardToStr(Player* p1, Player* p2);

  // Splits a string by the passed in character d
  std::vector<std::string> split(const std::string &s, char d);

 private:
  // Player 1
  Player* p1;

  // Player 2
  Player* p2;

  // List of current walls on the board
  // Wall walls[20];
  std::unordered_set<std::string> walls;

  // Number of walls placed in game
  int numWalls;

  // 0 = player 1, 1 = player 2
  int turn;

  // Board bound
  double bound;
};

class Board {
    public:
    Player players[2];
    std::unordered_set<std::string> walls;

    Board makeMove(Board b, std::string action, int turn);
};

#endif
