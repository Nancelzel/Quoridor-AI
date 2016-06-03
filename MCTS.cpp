#include "MCTS.h"
#include <iterator>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <assert.h>

using namespace std;

float MCTS::ucb(string board) {
    assert(plays.count(board));
    assert(losses.count(board));

    return ((float) losses[board]) / plays[board] + sqrt(2 * log(plays[board])
            /total_plays);
}

string MCTS::randomMove(vector<string> actions) {
    // Count number of moves in legal actions
    unsigned int num_move = 0;
    int action;
    int randMove;
    for (vector<string>::iterator it = actions.begin();
            it != actions.end(); it ++){
        if ((*it)[0] == 'm') {
            num_move++;
        }
    }

    // Generate random bit to determine which action to take
    action = rand() % 2;

    // If no legal walls to place, move
    if (num_move == actions.size()) {
        action = 0;
    }

    // If action is 0, move
    if (action == 0) {
        randMove = rand() % num_move;
    }
    // If action is 1, place a wall
    else {
        randMove = rand() % (actions.size() - num_move) + num_move;
    }
    return actions[randMove];
}
        

void MCTS::train(int iterations) {
    Quoridor* q;
    vector<string> actions;
    unordered_set<string> visited_states;
    vector<string> poss_states;
    string chosenMove;
    bool expand;
    int winner;
    char turn_cmp;
    float max_ucb;

    for (int i = 0; i < iterations; i++) {
        q = new Quoridor();
        winner = -1;
        expand = true;
        visited_states.clear();
        string state = q->boardToStr(q->currPlayer(), q->opposingPlayer());


        while (winner == -1) {
            actions = q->getLegalMoves(q->currPlayer(), q->opposingPlayer());

            // Get list of possible states
            poss_states.clear();
            for (vector<string>::iterator it = actions.begin();
                    it != actions.end(); it ++){
                // Copy the board, then apply the action to it
                Quoridor q_copy = Quoridor(*q);
                q_copy.makeMove(*it);
                poss_states.push_back(q_copy.boardToStr(q_copy.currPlayer(),
                    q_copy.opposingPlayer()));
            }

            // Find max UCB:
            max_ucb = 0.;
            // Use another iterator to track action taken to get to a certain
            // state.
            vector<string>::iterator act_it = actions.begin();
            for (vector<string>::iterator it = poss_states.begin();
                    it != poss_states.end(); it ++){
                // If not all children have data, choose randomly
                if (plays.count(*it) == 0) {
                    chosenMove = randomMove(actions);
                    break;
                }
                // Update max if needed
                if (ucb(*it) > max_ucb) {
                    chosenMove = *act_it;
                    max_ucb = ucb(*it);
                }
                act_it ++;
            }

            // Make the move
            q->makeMove(chosenMove);
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
            if (plays.count(*it) == 0) {
                continue;
            }
            if ((*it)[0] == turn_cmp) {
                losses[*it]++;
            }
            plays[*it]++;
        }

    }
}
