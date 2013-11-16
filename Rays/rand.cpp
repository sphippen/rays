#include <cstdlib>
#include "rand.h"

namespace spr
{

  int randInt()
  {
    return rand();
  }

  int randMax()
  {
    return RAND_MAX;
  }

  double randDouble()
  {
    return static_cast<double>(randInt()) / static_cast<double>(RAND_MAX);
  }
  void seedRand(unsigned int seed)
  {
    srand(seed);
  }
}