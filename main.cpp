#include <cstdlib>
#include <iostream>
#include <opencv2/core.hpp>

#include "gp.hpp"
#include "program.hpp"

#define MAX_DEPTH 2

int main( int argc, char** argv ) {	
    if(argc < 11){
        std::cout << "./mechanical_draw <individuos> <elitism> <maxDepth> <pcross> <pmul> <mulType> <epochs> <nThreads> <imgSrc> <imgDst>" << std::endl;
        return 1;
    }

    std::string outputFile = "";

    outputFile += argv[10];
    for(int i=1;i<argc-2;i++){
        outputFile += "_" + (std::string)argv[i];
    }
	cv::Mat originalImg = cv::imread(argv[9] , CV_LOAD_IMAGE_GRAYSCALE);

	GP gp = GP(
        std::stoi(argv[1]),
        std::stoi(argv[2]),
        std::stoi(argv[3]),
        std::stod(argv[4]),
        std::stod(argv[5]),
        originalImg,
        std::stoi(argv[8])
    );

    for(int i=0; i<10; i++){
        gp.run(std::stoi(argv[6]), std::stoi(argv[7]), "exec_" + (std::string)(i) + "_" + outputFile);
    }
 
	return 0;
}

