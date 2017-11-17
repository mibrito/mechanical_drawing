#ifndef __PRIMITIVES_H_INCLUDED__
#define __PRIMITIVES_H_INCLUDED__

#include <list>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#define MAX_DRAWS 2
#define MAX_PRIMITIVES 4

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

  virtual void draw(cv::Mat const& img) const;
  
  virtual bool equals(const Draw &d) const;

  static std::vector<Draw*> generate(int const& maxDepth, int const& w, int const& h);

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
  int thickness;

  explicit Line (const Line &l);
  Line (cv::Point const& p1, cv::Point const& p2, cv::Scalar const& color, int const& thickness);
  virtual ~Line(){}
  virtual Line* clone() const;

  virtual void draw(cv::Mat const& img) const;
  virtual bool equals(const Draw &d) const;

  static Line* generateRandom(int width, int height);
};

// class Triangle: public Draw {
// protected:
//   virtual void print(std::ostream& out) const;
  
// public:
//   cv::Point p1;
//   cv::Point p2;
//   cv::Point p3;
//   cv::Scalar color;

//   explicit Triangle (const Triangle &l);
//   Triangle (cv::Point const& p1, cv::Point const& p2, cv::Point const& p3 cv::Scalar const& color);
//   virtual ~Triangle(){}
//   virtual Triangle* clone() const;

//   virtual void draw(cv::Mat const& img) const;
//   virtual bool equals(const Draw &d) const;

//   static Triangle* generateRandom(int width, int height);
// };

// class Color: public Draw {

// }

#endif
