#include <ctime>
#include <cstdlib>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "test.hpp"
#include "grammar.hpp"

#define HEIGHT 512
#define WIDTH 512

int main( void ) {
  srand (time(NULL));
  // drawRandomLines();

  cv::Mat img (WIDTH, HEIGHT, CV_8UC1, cv::Scalar(255));
  Program p = Program::generateRandom(WIDTH, HEIGHT);
  Program::draw(img, p);

  cv::namedWindow( "Display window", WINDOW_AUTOSIZE );
  cv::imshow( "Display window", img );
  
  cv::waitKey(0);

  std::cout << p << std::endl;

  return 0;
}