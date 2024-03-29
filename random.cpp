#include "random.hpp"

unsigned R::seed = 345;
std::default_random_engine R::generator (R::seed);

double R::runif () { return distRealUniform(R::generator); }
int R::iunif () { return distIntUniform(R::generator); }
int R::gray () { return distGray(R::generator); }
int R::x () { return distX(R::generator); }
int R::y () { return distY(R::generator); }
int R::thickness () {
  // return distThickness2(R::generator);
  // return distThickness(R::generator);
  return 1;
}
int R::thickness2 () {
  return distThickness2(R::generator);
}
int R::mutationAll() { return distMutationAll(R::generator); }
int R::mutationNTree() { return distMutationNTree(R::generator); }
int R::mutationChangeLeaf() { return distMutationChangeLeaf(R::generator); }
