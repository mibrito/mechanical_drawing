#ifndef __RANDOM_H_INCLUDE__
#define __RANDOM_H_INCLUDE__

#include <chrono>
#include <random>
#include <climits>
#include <iostream>
#include <algorithm>

class R {
private:
  static unsigned seed;
  static std::default_random_engine generator;
public:
  std::uniform_real_distribution<double> distRealUniform;
  std::uniform_int_distribution<int> distIntUniform;
  std::uniform_int_distribution<int> distGray ;
  std::uniform_int_distribution<int> distX;
  std::uniform_int_distribution<int> distY;
  std::uniform_int_distribution<int> distThickness;
  std::uniform_int_distribution<int> distThickness2;
  std::uniform_int_distribution<int> distMutation;
  std::uniform_int_distribution<int> distMutationChangeLeaf;

  R() {}
  R(int const& width, int const &height) {
    distRealUniform = std::uniform_real_distribution<double> (0.0, 1.0);
    distIntUniform = std::uniform_int_distribution<int> (1,INT_MAX);
    distGray = std::uniform_int_distribution<int> (1,255);
    distX = std::uniform_int_distribution<int> (1, width) ;
    distY = std::uniform_int_distribution<int> (1, height);
    distThickness = std::uniform_int_distribution<int> (1, (int)std::min(width,height));
    distThickness2 = std::uniform_int_distribution<int> (1,2);
    distMutation = std::uniform_int_distribution<int> (0, 4);
    distMutationChangeLeaf = std::uniform_int_distribution<int> (0, 7);
  }

  double runif ();
  int iunif ();
  int gray ();
  int x ();
  int y ();
  int thickness ();
  int thickness2 ();
  int mutation ();
  int mutationChangeLeaf ();
};

#endif
