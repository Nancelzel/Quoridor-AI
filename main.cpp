#include "Quoridor.h"

int main() {
  Quoridor quoridor;
  std::string input = "y";
  while (input == "y") {
    quoridor.play();
    std::cout << "Would you like to play again? (y/n) > ";
    getline(std::cin, input);
    std::cout << std::endl;
  }

  std::cout << "Bye!" << std::endl;
  return 1;
}
