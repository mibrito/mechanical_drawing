#include <ctime>
#include <cstdlib>
#include <iostream>
#include <opencv2/core.hpp>

#include "test.hpp"
#include "program.hpp"

#define MAX_DEPTH 2
#define HEIGHT 512
#define WIDTH 512

void showDraw(Program p){
	cv::Mat img (WIDTH, HEIGHT, CV_8UC1, cv::Scalar(255));

	p.draw(img);

	cv::imshow("Show Draw", img);
	cv::waitKey(0);
}


int main( void ) {
	srand (345);
	
	cv::Mat originalImg = cv::imread("./pics/lennabw.jpg" , CV_LOAD_IMAGE_GRAYSCALE);

	auto A = new Program(originalImg.size[0], originalImg.size[1]);
	auto B = new Program(originalImg.size[0], originalImg.size[1]);
	A->fillRandomNodes(MAX_DEPTH);
	B->fillRandomNodes(MAX_DEPTH);

	auto children = Program::crossover(A, B);

	delete A;
	delete B;

	delete children[0];
	delete [] children;

	return 0;
}

