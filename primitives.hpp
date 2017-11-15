#ifndef __PRIMITIVES_H_INCLUDED__
#define __PRIMITIVES_H_INCLUDED__

#include <vector>
#include <cstdlib>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using std::rand;

#define MAX_GRAY 255
#define RANDINT(UPPER) (rand() % UPPER)

class Draw {
protected:
  virtual void print(std::ostream& out) const;
public:
  int depth;
  std::vector<Draw*> drawings;

  explicit Draw (const Draw &d);
  explicit Draw (int d);
  virtual ~Draw();

  virtual Draw* clone() const;

  virtual void draw(cv::Mat img) const;
  
  virtual bool equals(const Draw &d) const;

  friend std::ostream& operator<< (std::ostream& out, const Draw& bd) {
    bd.print(out);
    return out;
  }
  friend std::ostream& operator<< (std::ostream& out, const Draw* bd) {
    bd->print(out);
    return out;
  }
};

class Line: public Draw {
protected:
  virtual void print(std::ostream& out) const;
  
public:
  cv::Point p1;
  cv::Point p2;
  cv::Scalar color;

  explicit Line (const Line &l);
  Line (cv::Point p1, cv::Point p2, cv::Scalar color);
  virtual ~Line(){}
  virtual Line* clone() const;

  virtual void draw(cv::Mat img) const;
  virtual bool equals(const Draw &d) const;

  static Line* generateRandom(int width, int height);
};

#endif
