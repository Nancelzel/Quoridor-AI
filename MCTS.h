#ifndef MCTS_H_
#define MCTS_H_
#include "Quoridor.h"
#include<unordered_map>

class MCTS {
    public:
    void train(int iterations);
    std::string dumps();
    void loads(std::string pickle);

    private:
    std::unordered_map<std::string, int> plays;
    std::unordered_map<std::string, int> losses;
};
#endif
