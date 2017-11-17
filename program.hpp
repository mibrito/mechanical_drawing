#ifndef __PROGRAM_H_INCLUDED__
#define __PROGRAM_H_INCLUDED__

#include <fstream>
#include <vector>
#include <list>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <opencv2/core.hpp>
#include "random.hpp"
#include "primitives.hpp"

#define MAX_DRAWS 2
#define MAX_PRIMITIVES 4

#define MAX_MUTATION_DEPTH 1

#define MUTATION_LEAF 0
#define MUTATION_TREE 1
#define MUTATION_MIXED 3

class Program {
private:
  R rand;

public:
	int width, height;

	cv::Scalar fitness = cv::Scalar(std::numeric_limits<float>::max());
	std::vector<Draw*> nodes;

	explicit Program(const Program &p);
	Program(int const& width, int const& height);
	virtual ~Program();
  virtual Program* clone() const;

  void draw(cv::Mat const& img);
  void show();
  void saveImage(const char* filename);
  void saveProgram(const char* filename);
  cv::Scalar calculateFitness(cv::Mat const& originalImg);
  void fillRandomNodes(int maxDepth);
  int changePoint();

  Program* crossover(Program *pB, int const& cpA, int const& cpB);
  void mutation(int const& type);
  void mutationLeaf();
  void mutationTree();

	static Program* generateRandomNodes(int maxDepth, const int& w, const int& h);
	static Program** crossover(Program* parentA, Program* parentB);

	friend std::ostream& operator<<(std::ostream &strm, const Program &p) {
		return strm << "P" << p.nodes.size() << "(" << p.nodes.front() << ")";
	}
	friend std::ostream& operator<<(std::ostream &strm, const Program *p) {
		return strm << "P" << p->nodes.size() << "(" << p->nodes.front() << ")";
	}

	friend bool operator<(const Program &a, const Program &b) {
		return a.fitness[0] < b.fitness[0];
	}
  
  static bool compare(Program *a, Program *b){
    return a->fitness[0] < b->fitness[0];
  }
};

#endif