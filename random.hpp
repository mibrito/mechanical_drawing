#ifndef __RANDOM_H_INCLUDE__
#define __RANDOM_H_INCLUDE__

#include <climits>
#include <chrono>
#include <random>
#include <algorithm>

class R {
private:
  static unsigned seed;
  static std::default_random_engine generator;
public:
  std::uniform_real_distribution<double> distRealUniform {0.0, 1.0};
  std::uniform_int_distribution<int> distIntUniform {1,INT_MAX};
  std::uniform_int_distribution<int> distGray {1,255};
  std::uniform_int_distribution<int> distX;
  std::uniform_int_distribution<int> distY;
  std::uniform_int_distribution<int> distThickness;

  R() {}
  R(int const& width, int const &height)
    : distX{ std::uniform_int_distribution<int> {1, width} },
      distY{ std::uniform_int_distribution<int> {1, height} },
      distThickness{ std::uniform_int_distribution<int> {1, std::min((int) (width*5)/100, (int)(height*5)/100) } }
  {}

  double runif ();
  int iunif ();
  int gray ();
  int x ();
  int y ();
  int thickness ();
};

#endif
