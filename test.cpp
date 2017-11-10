#include <opencv2/highgui.hpp>
#include <iostream>
#include <random>
#include "primitives.hpp"

#define w 255

using namespace std;
using namespace cv;

void drawPics (void) {
  Mat image;
  image = cv::imread("./pics/vanessa.jpg" , CV_LOAD_IMAGE_COLOR);
  
  if(! image.data ) {
      cout <<  "Could not open or find the image" << endl ;
      return;
    }
  
  namedWindow( "Display window", WINDOW_AUTOSIZE );
  imshow( "Display window", image );
  
  waitKey(0);
}

void drawRandomLines (void) {
  char rand_window[] = "Draw Random Lines";
  Mat img ( w, w, CV_8UC1, Scalar(255));

  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(1,w);
  auto dice = std::bind ( distribution, generator );

  Line ln1 (Point(dice(), dice()), Point(dice(), dice()), Scalar(119));
  Line ln2 (Point(dice(), dice()), Point(dice(), dice()), Scalar(119));
  ln1.draw(img);

  cout << "img = " << endl << ln1.p1 << endl;

  namedWindow(rand_window, WINDOW_AUTOSIZE );
  imshow(rand_window, img);
  waitKey(0);

  ln2.draw(img);
  imshow(rand_window, img);
  waitKey(0);
}
