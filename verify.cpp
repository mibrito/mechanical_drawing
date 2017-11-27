#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global variables

int difference_type = 1;
int const max_type = 3;

Mat orig, res, dst;
const char* window_name = "Threshold Demo";

const char* trackbar_type = "Type: \n 0: bitwise_and \n 1: bitwise_or \n 2: bitwise_or \n 3: bitwise_not";
const char* trackbar_value = "Value";

/// Function headers
void difference( int, void* );

/**
 * @function main
 */
int main( int argc, char** argv )
{
  /// Load an image
  orig = imread( argv[1],CV_LOAD_IMAGE_GRAYSCALE );
  res = imread( argv[2],CV_LOAD_IMAGE_GRAYSCALE );

  /// Create a window to display results
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );

  /// Create Trackbar to choose type of Threshold
  createTrackbar( trackbar_type,
                  window_name, &difference_type,
                  max_type, difference );

  // createTrackbar( trackbar_value,
  //                 window_name, &threshold_value,
  //                 max_value, Threshold_Demo );

  /// Call the function to initialize
  difference( 0, 0 );

  /// Wait until user finishes program
  while(true)
  {
    int c;
    c = waitKey( 20 );
    if( (char)c == 27 )
      { break; }
   }

}


/**
 * @function Threshold_Demo
 */
void difference( int, void* )
{
  /* 0: Binary
     1: Binary Inverted
     2: Threshold Truncated
     3: Threshold to Zero
     4: Threshold to Zero Inverted
   */

  switch(difference_type){
    case 0:
      bitwise_and(orig, res, dst);
      break;
    case 1:
      bitwise_or(orig, res, dst);
      break;
    case 2:
      bitwise_xor(orig, res, dst);
      break;
    case 3:
      bitwise_not(orig, dst);
      break;
  }
  

  imshow( window_name, dst );
}