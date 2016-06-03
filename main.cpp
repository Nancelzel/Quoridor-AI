#include "Quoridor.h"

#include "AI.h"
#include "Randomizer.h"
#include "BruteWayne.h"

#include <ctime>
#include <cstdlib>

int main() {
  srand(time(NULL));
  
  // Quoridor* quoridor = new Quoridor();
  Quoridor quoridor;
  
  AI* ai1 = new Randomizer();
  AI* ai2 = new Randomizer();
  // AI* ai3 = new BruteWayne();
  // ai2->q = quoridor;
  // ai3->q = quoridor;
  // std::cout << ai1->getNextMove() << std::endl;
  // std::cout << ai2->getNextMove() << std::endl;
  // std::cout << ai3->getNextMove() << std::endl;

  quoridor.playAI(ai1, ai2);

  // TODO: Board must be updated every iteration?
  /*
  std::string input = "y";
  while (input == "y") {
    quoridor.play();
    std::cout << "Would you like to play again? (y/n) > ";
    getline(std::cin, input);
    std::cout << std::endl;
  }

  std::cout << "Bye!" << std::endl;
  */
  return 1;
}
