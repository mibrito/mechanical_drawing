#include <cstdlib>
#include <iostream>
#include <opencv2/core.hpp>

#include "gp.hpp"
#include "program.hpp"

#define MAX_DEPTH 2

int main( int argc, char** argv ) {	
  if(argc < 10){
    std::cout << "./mechanical_draw <individuos> <elitism> <maxDepth> <pcross> <pmul> <epochs> <nThreads> <imgSrc> <imgDst>" << std::endl;
    return 1;
  }

	cv::Mat originalImg = cv::imread(argv[8] , CV_LOAD_IMAGE_GRAYSCALE);

	GP gp = GP(
    std::stoi(argv[1]),
    std::stoi(argv[2]),
    std::stoi(argv[3]),
    std::stod(argv[4]),
    std::stod(argv[5]),
    originalImg,
    std::stoi(argv[7])
  );

  gp.run(std::stoi(argv[6]));
  
  std::cout << gp.population.front()->fitness << std::endl;

  gp.population.front()->saveImage(argv[9]);
  
  // auto p = Program::generateRandomNodes(2, 512, 512);

  // std::cout << p << std::endl;

  // delete p;

	return 0;
}

