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
  int width, height;
  std::uniform_real_distribution<double> distRealUniform {0.0, 1.0};
  std::uniform_int_distribution<int> distIntUniform {1,INT_MAX};
  std::uniform_int_distribution<int> distGray {1,255};
  std::uniform_int_distribution<int> distX;
  std::uniform_int_distribution<int> distY;
  std::uniform_int_distribution<int> distThickness;
  std::gamma_distribution<double> distThickness2{2.0,2.0};

  R() {}
  R(int const& width, int const &height)
    : width{width}, height{height},
      distX{ std::uniform_int_distribution<int> {1, width} },
      distY{ std::uniform_int_distribution<int> {1, height} },
      distThickness{ std::uniform_int_distribution<int> {1, (int)std::min(width,height) } }
  {}

  double runif ();
  int iunif ();
  int gray ();
  int x ();
  int y ();
  int thickness ();
  int thickness2 ();
};

#endif
