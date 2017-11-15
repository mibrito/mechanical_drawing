#ifndef __GP_H_INCLUDED__
#define __GP_H_INCLUDED__

#include <vector>
#include <opencv2/core.hpp>

#include "program.hpp"
#include "primitives.hpp"

class GP {
private:
  int nIndividuals, maxDepth;
  int width, height;
  std::vector<Program*> population;

public:
  GP (const int &nIndividuals, const int &maxDepth, const int &width, const int &height);
  ~GP();

  void generateIndividuals();
  void calculateFitness(cv::Mat originalImg);

  int* sample(const int &m, const int &n);
};

#endif