#ifndef __GRAMMAR_H_INCLUDED__
#define __GRAMMAR_H_INCLUDED__

#include <vector>
#include <cstdlib>
#include <iostream>
#include <opencv2/core.hpp>
#include "primitives.hpp"

#define MAX_CHILDREN 2
#define MAX_PRIMITIVES 2

class Program {
  public:
    std::vector<Line> lines;
    std::vector<Program> children;

    static void draw(cv::Mat img, const Program& root){
      for(Program p: root.children){
        Program::draw(img, p);
      }
      for(Line l: root.lines){
        l.draw(img);
      }
    }

    static Program generateRandom(const int& width, const int& height){
      Program root = Program();
      int i = 0;
      while(std::rand()%2 > 0 && i++ < MAX_CHILDREN){
        root.children.push_back(Program::generateRandom(width, height));
      }

      i=0;
      while(std::rand()%2 > 0 && i++ < MAX_PRIMITIVES){
        root.lines.push_back(Line::generateRandom(width, height));
      }

      return root;
    }

    friend std::ostream& operator<<(std::ostream &strm, const Program &root) {
      strm << "P( ";
      for(Program p: root.children){
        strm << p;
      }
      for(Line l: root.lines){
        strm << l;
      }
      strm << " )";

      return strm;
    }

};

#endif