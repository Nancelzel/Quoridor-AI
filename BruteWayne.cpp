#include "BruteWayne.h"
#include <algorithm>
#include <float.h>
#include <queue>
#include <string>
#include <utility>

bool operator<(const Node& lhs, const Node& rhs) {
  return lhs.second < rhs.second;
}

std::string BruteWayne::getNextMove() {
  return "TODO: implement this";
  // Choose whether to move or wall.
  // If wall, choose a random wall.
  if (moveOrWall() == 0) {
    std::vector<std::string> possible_walls = q.legalWalls(q.currPlayer(), q.opposingPlayer());
    std::random_shuffle(possible_walls.begin(), possible_walls.end());
    return possible_walls[0];
  }
  // If move, use Dijkstra's algorithm.
  std::vector<std::vector<double>> dist(9, std::vector<double>(9, DBL_MAX));
  std::vector<std::vector<bool>> visited(9, std::vector<bool>(9, false));
  std::vector<std::vector<std::pair<int, int>>> prev(9, std::vector<std::pair<int, int>>(9, std::make_pair(-1, -1)));
  dist[q.currPlayer()->x][q.currPlayer()->y] = 0;

  std::priority_queue<Node, std::vector<Node>> pq;

  // TODO: Make sure p1.x and p1.y are 0 to 17.
  for (int row = 0; row < 9; ++row) {
    for (int col = 0; col < 9; ++col) {
      if (2 * row - 1 == q.currPlayer()->x && 2 * col - 1 == q.currPlayer()->y)
	pq.push(std::make_pair(std::make_pair(row, col), 0.0));
      else
	pq.push(std::make_pair(std::make_pair(row, col), DBL_MAX));
    }
  }

  while (!pq.empty()) {
    Node u = pq.top(); // Source node will be selected first.
    int x = u.first.first;
    int y = u.first.second;
    visited[x][y] = true;
    pq.pop();

    // North
    if (q.isLegalMove(q.currPlayer(), q.opposingPlayer(), 2*(x - 1)-1, 2*y-1) && !visited[x - 1][y]) {
      double alt = dist[x][y] + 1;
      if (alt < dist[x-1][y]) {
	dist[x-1][y] = alt;
	prev[x-1][y] = std::make_pair(x, y);
      }
    }
	
    // South
    if (q.isLegalMove(q.currPlayer(), q.opposingPlayer(), 2*(x + 1)-1, 2*y-1) && !visited[x + 1][y]) {
      double alt = dist[x][y] + 1;
      if (alt < dist[x+1][y]) {
	dist[x+1][y] = alt;
	prev[x+1][y] = std::make_pair(x, y);
      }
    }
    
    // East
    if (q.isLegalMove(q.currPlayer(), q.opposingPlayer(), 2*x-1, 2*(y + 1)-1) && !visited[x][y+1]) {
      double alt = dist[x][y] + 1;
      if (alt < dist[x][y+1]) {
	dist[x][y+1] = alt;
	prev[x][y+1] = std::make_pair(x, y);
      }
    }

    // West
    if (q.isLegalMove(q.currPlayer(), q.opposingPlayer(), 2*x-1, 2*(y - 1)-1) && !visited[x][y-1]) {
      double alt = dist[x][y] + 1;
      if (alt < dist[x][y-1]) {
	dist[x][y-1] = alt;
	prev[x][y-1] = std::make_pair(x, y);
      }
    }
  }

  int endgame_col = 1;
  if (q.getTurn())
    endgame_col = 9;

  int lowest_score = dist[0][endgame_col];
  int endgame_row = 0;
  for (int i = 0; i < 9; ++i) {
    if (dist[i][endgame_col] < lowest_score) {
      endgame_row = i;
      lowest_score = dist[i][endgame_col];
    }
  }

  std::pair<int, int> next_move = std::make_pair(endgame_row, endgame_col);
  while (prev[next_move.first][next_move.second] != std::make_pair(q.currPlayer()->x, q.currPlayer()->y)) {
    next_move = prev[next_move.first][next_move.second];
  }
  
  return "m " + std::to_string(2 * next_move.first - 1) + " " + std::to_string(2 * next_move.second - 1);
}

// TODO: Make sure to seed rand in both BruteWayne and Randomizer.
int BruteWayne::moveOrWall() {
  // AI has no more walls to place down, will strictly move
  if(q.getNumWalls() == 10)
    return 0;

  return rand() % 2;
}
