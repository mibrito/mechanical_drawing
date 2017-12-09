#include <cstdlib>
#include <iostream>
#include <opencv2/core.hpp>
#include <chrono>

#include "gp.hpp"
#include "program.hpp"

#define MAX_DEPTH 2

using namespace std::chrono;

int main( int argc, char** argv ) {	
	if(argc < 11){
		std::cout << "./mechanical_draw <individuos> <elitism> <maxDepth> <pcross> <pmul> <mulType> <epochs> <nThreads> <imgSrc> <imgDst>" << std::endl;
		return 1;
	}

	std::string outputFile = "";

	// outputFile += argv[10];
	for(int i=1;i<argc-2;i++){
		outputFile += "_" + (std::string)argv[i];
	}
	cv::Mat originalImg = cv::imread(argv[9] , CV_LOAD_IMAGE_GRAYSCALE);

	
	for(int i=0; i<10; i++){
		GP *gp = new GP(
				std::stoi(argv[1]),
				std::stoi(argv[2]),
				std::stoi(argv[3]),
				std::stod(argv[4]),
				std::stod(argv[5]),
				originalImg,
				std::stoi(argv[8])
		);

		std::cout << "execution_" << i << "_" << std::endl;
		std::string out = std::string(argv[10]) + "_exec_" + std::to_string(i) + outputFile;

		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		gp->run(std::stoi(argv[6]), std::stoi(argv[7]), out);
		high_resolution_clock::time_point t2 = high_resolution_clock::now();

		auto duration = duration_cast<milliseconds>( t2 - t1 ).count();

		std::cout << "duration_" << duration << "_" << std::endl;
		
		delete gp;
	}
 
	return 0;
}

