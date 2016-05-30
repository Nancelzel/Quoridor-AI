#include "Player.h"
#include "Wall.h"

class Quoridor {
 public:
  // Constructor
  Quoridor() {
    // Player 1 starts at the left side of board
    p1.name = "Player 1";
    p1.x = 1;
    p1.y = 9;
    p1.numWalls = 10;

    // Player 2 starts at the right side of board
    p2.name = "Player 2";
    p2.x = 17;
    p2.y = 9;
    p2.numWalls = 10;
    
    // Start with player 1
    turn = 0;
    numWalls = 0;
    bound = 9;
  }  

  // Checks if player move is legal
  bool isLegalMove(Player p1, Player p2, double x, double y);

  // Checks if wall placed is legal
  bool isLegalWall(Player p);

  // Updates current player's position
  void updatePlayer(Player p1, Player p2, int x, int y);

  // Add a wall on the board
  void updateWall(int sX, int sY, int eX, int eY);

  // Checks if a player has won
  int isGameOver();

  // Displays the board
  void displayBoard();

  // Play a game of Quoridor.
  void play();

 private:
  // Player 1
  Player p1;

  // Player 2
  Player p2;

  // List of current walls on the board
  Wall walls[20];

  // Number of walls placed in game
  int numWalls;

  // 0 = player 1, 1 = player 2
  int turn;

  // Board bound
  double bound;
};
