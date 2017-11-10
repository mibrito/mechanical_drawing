#ifndef __PRIMITIVES_H_INCLUDED__
#define __PRIMITIVES_H_INCLUDED__

#include <cstdlib>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using std::rand;
using namespace cv;

#define MAX_GRAY 255
#define RANDINT(UPPER) ((rand() % UPPER-1)+1)

class Line {
  public:
    Point p1;
    Point p2;
    Scalar color;

    Line (Point p1, Point p2, Scalar color) {
      this->p1 = p1;
      this->p2 = p2;
      this->color = color;
    }
    void draw(Mat img) {
      line(img, p1, p2, color, 1, LINE_8);
    }

    static Line generateRandom(int width, int height) {
      return Line(
        Point(RANDINT(width), RANDINT(height)),
        Point(RANDINT(width), RANDINT(height)),
        Scalar(RANDINT(MAX_GRAY))
      );
    }

    friend std::ostream& operator<<(std::ostream &strm, const Line &l) {
      strm << "Line( " << l.p1 << "," << l.p2 << "," << l.color << " )";
      return strm;
    }
};

#endif
