#include <opencv2/highgui.hpp>
#include <iostream>
#include <random>
#include "primitives.hpp"

#define w 255

void drawPics (void) {
  cv::Mat image;
  image = cv::imread("./pics/Vanessa.jpg" , CV_LOAD_IMAGE_COLOR);
  
  if(! image.data ) {
      std::cout <<  "Could not open or find the image" << std::endl ;
      return;
    }
  
  cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE );
  cv::imshow( "Display window", image );
  
  cv::waitKey(0);
}

void drawRandomLines (void) {
  char rand_window[] = "Draw Random Lines";
  cv::Mat img ( w, w, CV_8UC1, cv::Scalar(255));

  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(1,w);
  auto dice = std::bind ( distribution, generator );

  Line ln1 (cv::Point(dice(), dice()), cv::Point(dice(), dice()), cv::Scalar(119));
  Line ln2 (cv::Point(dice(), dice()), cv::Point(dice(), dice()), cv::Scalar(119));
  ln1.draw(img);

  std::cout << "img = " << std::endl << ln1.p1 << std::endl;

  cv::namedWindow(rand_window, cv::WINDOW_AUTOSIZE );
  cv::imshow(rand_window, img);
  cv::waitKey(0);

  ln2.draw(img);
  cv::imshow(rand_window, img);
  cv::waitKey(0);
}
