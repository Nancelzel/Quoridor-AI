#include "BruteWayne.h"
#include <algorithm>
#include <float.h>
#include <queue>
#include <string>
#include <utility>

std::string BruteWayne::getNextMove() {
  // Choose whether to move or wall.
  // If wall, choose a random wall.
  if (moveOrWall() == 1) {
    std::vector<std::string> possible_walls = q->legalWalls(q->currPlayer(), q->opposingPlayer());
    std::random_shuffle(possible_walls.begin(), possible_walls.end());
    return possible_walls[0];
  }
  // If move, use Dijkstra's algorithm.
  std::vector<std::vector<double>> dist(9, std::vector<double>(9, DBL_MAX));
  std::vector<std::vector<bool>> visited(9, std::vector<bool>(9, false));
  std::vector<std::vector<Node*>> nodes;
  std::vector<std::vector<std::pair<int, int>>> prev(9, std::vector<std::pair<int, int>>(9, std::make_pair(-1, -1)));
  dist[(q->currPlayer()->x - 1) / 2][(q->currPlayer()->y - 1) / 2] = 0;

  std::unordered_set<Node*> pq;

  for (int row = 0; row < 9; ++row) {
    std::vector<Node*> row_nodes;
    for (int col = 0; col < 9; ++col) {
      int new_row = 2 * (row + 1) - 1;
      int new_col = 2 * (col + 1) - 1;
      Node* new_node = new Node();
      new_node->first = std::make_pair(row, col);
      if (new_row == q->currPlayer()->x && new_col == q->currPlayer()->y) {
	new_node->second = 0.0;
      }
      else {
	new_node->second = DBL_MAX;
      }
      pq.insert(new_node);
      row_nodes.push_back(new_node);
    }
    nodes.push_back(row_nodes);
  }

  while (!pq.empty()) {
    // Get node with smallest distance. Source node will be selected first.
    Node* u = *pq.begin();
    for (auto it = pq.begin(); it != pq.end(); ++it) {
      if ((*it)->second < u->second) {
	u = *it;
      }
    }
    
    int row = u->first.first;
    int col = u->first.second;
    int convert_row = 2 * row + 1;
    int convert_col = 2 * col + 1;
    visited[row][col] = true;
    pq.erase(u);

    // North
    if (row - 1 >= 0 && !q->isAlreadyWall(convert_row - 1, convert_col) && !visited[row - 1][col]) {
      double alt = dist[row][col] + 1;
      if (alt < dist[row-1][col]) {
	dist[row-1][col] = alt;
	nodes[row-1][col]->second = alt;
	prev[row-1][col] = std::make_pair(row, col);
      }
    }
	
    // South
    if (row + 1 <= 8 && !q->isAlreadyWall(convert_row + 1, convert_col) && !visited[row + 1][col]) {
      double alt = dist[row][col] + 1;
      if (alt < dist[row+1][col]) {
	dist[row+1][col] = alt;
	nodes[row+1][col]->second = alt;
	prev[row+1][col] = std::make_pair(row, col);
      }
    }
    
    // East
    if (col + 1 <= 8 && !q->isAlreadyWall(convert_row, convert_col + 1) && !visited[row][col + 1]) {
      double alt = dist[row][col] + 1;
      if (alt < dist[row][col+1]) {
	dist[row][col+1] = alt;
	nodes[row][col+1]->second = alt;
	prev[row][col+1] = std::make_pair(row, col);
      }
    }

    // West
    if (col - 1 >= 0 && !q->isAlreadyWall(convert_row, convert_col - 1) && !visited[row][col - 1]) {
      double alt = dist[row][col] + 1;
      if (alt < dist[row][col-1]) {
	dist[row][col-1] = alt;
	nodes[row][col-1]->second = alt;
	prev[row][col-1] = std::make_pair(row, col);
      }
    }
  }

  int endgame_col = 8; // Player 1 wants to reach the right side.
  if (q->getTurn())
    endgame_col = 0; // Player 2 wants to reach the left side.

  int lowest_score = dist[0][endgame_col];
  int endgame_row = 0;
  for (int i = 0; i < 9; ++i) {
    if (dist[i][endgame_col] < lowest_score) {
      endgame_row = i;
      lowest_score = dist[i][endgame_col];
    }
  }

  std::pair<int, int> next_move = std::make_pair(endgame_row, endgame_col);
  while (prev[next_move.first][next_move.second] != std::make_pair((q->currPlayer()->x - 1) / 2, (q->currPlayer()->y - 1) / 2)) {
    if (next_move.first == -1 || next_move.second == -1) {
      std::cout << "This should never happen." << std::endl;
      break;
    }
    next_move = prev[next_move.first][next_move.second];
  }

  return "m " + std::to_string(2 * next_move.first + 1) + " " + std::to_string(2 * next_move.second + 1);
}

int BruteWayne::moveOrWall() {
  // AI has no more walls to place down, will strictly move
  if(q->getNumWalls() == 10)
    return 0;

  return rand() % 2;
}
