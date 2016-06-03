#include "MCTS.h"
#include <iterator>
#include <cmath>
#include <unordered_map>
#include <unordered_set>

using namespace std;


void MCTS::train(int iterations) {
    Quoridor* q;
    vector<string> actions;
    unordered_set<string> visited_states;
    vector<string> poss_states;
    int num_move;
    int choice;
    int action;
    string randMove;
    bool expand;
    int winner;
    char turn_cmp;

    for (int i = 0; i < iterations; i++) {
        q = new Quoridor();
        winner = -1;
        expand = true;
        visited_states.clear();
        string state = q->boardToStr(q->currPlayer(), q->opposingPlayer());


        while (winner == -1) {
            actions = q->getLegalMoves(q->currPlayer(), q->opposingPlayer());

            // Count number of moves in legal actions
            num_move = 0;
            for (vector<string>::iterator it = actions.begin();
                    it != actions.end(); it ++){
                if ((*it)[0] == 'm') {
                    num_move++;
                }
            }

            // Generate random bit to determine which action to take
            action = rand() % 2;
            // If action is 0, move
            if (action == 0) {
                randMove = rand() % num_move;
            }
            // If action is 1, place a wall
            else {
                randMove = rand() % (actions.size() - num_move) + num_move;
            }
            // Make the move
            q->makeMove(randMove);
            state = q->boardToStr(q->currPlayer(), q->opposingPlayer());

            // Expand the tree if needed
            if (expand && plays.count(state) == 0) {
                expand = false;
                plays[state] = 0;
                losses[state] = 0;
            }
            visited_states.insert(state);
            winner = q->isGameOver();
        }

        delete q;
        // Set compare term to check which states were losing
        if (winner == 0){
            turn_cmp = '1';
        }
        else {
            turn_cmp = '0';
        }

        // Iterate through visited states and update plays/losses
        for (unordered_set<string>::iterator it = visited_states.begin();
                it != visited_states.end(); it++){
            if ((*it)[0] == turn_cmp) {
                losses[*it]++;
            }
            plays[*it]++;
        }

//            q->makeMove(randMove);
//            poss_states = vector<string>;
//            for (vector<string>::iterator it = s.begin();
//                    it != s.end(); it ++){
//                poss_states.push_back
//        }
    }
}
