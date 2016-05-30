#include <string>

using namespace std;

class Quoridor {
 public:
  // Represents a player
  struct Player {

    string name;        // name of player
    double x;              // current x coordinate
    double y;              // current y coordinate
    int numWalls;       // number of walls player has left
  };

  // Represents a wall
  struct Wall {

    double sX;              // start x coordinate of wall
    double sY;              // start y coordinate of wall
    double eX;              // end x coordinate of wall
    double eY;              // end y coordinate of wall
  };
  
  // Quoridor constructor
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
  
  bool isLegalMove(Player p1, Player p2, double x, double y);  // Checks if player move is legal
  bool isLegalWall(Player p);                      // Checks if wall placed is legal
  void updatePlayer(Player p1, Player p2, int x, int y); // Updates current player's position
  void updateWall(int sX, int sY, int eX, int eY); // Add a wall on the board
  int isGameOver(Player p);                        // Checks if a player has won
  void displayBoard();                             // Displays the board

 private:
  Player p1;           // player 1
  Player p2;           // player 2
  Wall walls[20];      // list of current walls on the board
  int numWalls;        // number of walls placed in game
  int turn;            // 0 = player 1, 1 = player 2
  double bound;        // board bound
};
