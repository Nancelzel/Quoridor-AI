#ifndef AI_H_
#define AI_H_

#include "Quoridor.h"
#include <string>

class Quoridor;

class AI {
 public:
  /*
  AI(Quoridor& board) {
    q = new Quoridor();
    
  }

  ~AI() {
    delete q;
  }
  */

  virtual std::string getNextMove() { return "testing AI"; };

  Quoridor* q;
};

#endif
