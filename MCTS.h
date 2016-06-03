#ifndef MCTS_H_
#define MCTS_H_
#include "Quoridor.h"
#include<unordered_map>
#include<string>
#include<vector>

class MCTS {
    public:
    MCTS() {
        total_plays = 0;
    }
    float ucb(std::string board);
    std::string randomMove(std::vector<std::string> actions);
    void train(int iterations);
    std::string dumps();
    void loads(std::string pickle);

    private:
    std::unordered_map<std::string, int> plays;
    std::unordered_map<std::string, int> losses;
    int total_plays;
};
#endif
