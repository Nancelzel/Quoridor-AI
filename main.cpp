#include "Quoridor.h"

#include "AI.h"
#include "Randomizer.h"
#include "BruteWayne.h"

#include <fstream>
#include <ctime>
#include <cstdlib>

int main() {
  srand(time(NULL));
  std::ofstream out("testgame");
  Quoridor quoridor;
  
  AI* ai1 = new Randomizer();
  AI* ai2 = new BruteWayne();

  quoridor.playAI(ai1, ai2, out);
  return 1;
}
