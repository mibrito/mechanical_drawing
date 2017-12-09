#ifndef __GP_H_INCLUDED__
#define __GP_H_INCLUDED__

#include <vector>
#include <thread>
#include <algorithm>
#include <opencv2/core.hpp>

#include "random.hpp"
#include "program.hpp"
#include "primitives.hpp"

#define THREADS 4
#define MUTATION_DEPTH 1

class GP {
private:
  R rand;
  int width, height;
  int nIndividuals, elitism, maxDepth;
  double crossoverRate, mutationRate;
  cv::Mat originalImg;

  int nThreads;

public:
  std::vector<Program*> population;

  GP (
    int const& nIndividuals,
    int const& elitism,
    int const& maxDepth,
    double const& crossoverRate,
    double const& mutationRate,
    cv::Mat const& img,
    int const& nThreads
  );
  ~GP();

  void generateIndividuals();
  void calculateFitness();
  void sortByFitness();
  void crossover();
  void epoch(int const& mutationType);
  void run(int const& mutationType, int const& epoch, std::string &output);
  void printOutput(int const &epoch, int const& width);
  void saveImage(int const &epoch, std::string &output, int const& width);
  int* sample(const int &m, const int &n);
  
  static void calculateFitnessFn(std::vector<Program*> *population, cv::Mat const& originalImg, int begin, int const& end);
};

#endif
