#include "random.hpp"

unsigned R::seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine R::generator (R::seed);

double R::runif () { return distRealUniform(R::generator); }
int R::iunif () { return distIntUniform(R::generator); }
int R::gray () { return distGray(R::generator); }
int R::x () { return distX(R::generator); }
int R::y () { return distY(R::generator); }
int R::thickness () { return distThickness(R::generator); }
int R::thickness2 () {
  return (int)((distThickness2(R::generator) + 1)*std::min(width, height)/100);
}