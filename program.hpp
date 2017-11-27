#ifndef __PROGRAM_H_INCLUDED__
#define __PROGRAM_H_INCLUDED__

#include <fstream>
#include <vector>
#include <list>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "random.hpp"
#include "primitives.hpp"

#define MAX_DRAWS 2
#define MAX_PRIMITIVES 4

#define MAX_MUTATION_DEPTH 1

#define MUTATION_CHANGE_LEAF 0
#define MUTATION_LEAF 1
#define MUTATION_TREE 2
#define MUTATION_MIXED 3
#define MUTATION_MIXED_N_TREE 4

#define CHANGE_LEAF_P1 0
#define CHANGE_LEAF_P2 1
#define CHANGE_LEAF_H 2
#define CHANGE_LEAF_V 3
#define CHANGE_LEAF_HV 4
#define CHANGE_LEAF_R 5
#define CHANGE_LEAF_COLOR 6
#define CHANGE_LEAF_THICK 7

class Program {
private:
  R rand;

public:
	int width, height;

	double fitness = std::numeric_limits<float>::max();
	std::vector<Draw*> nodes;

	explicit Program(const Program &p);
	Program(int const& width, int const& height);
	virtual ~Program();
  virtual Program* clone() const;

  void draw(cv::Mat const& img);
  void show();
  void saveImage(std::string &filename);
  void saveProgram(std::string &filename);
  double calculateFitness(cv::Mat const& originalImg);
  void fillRandomNodes(int maxDepth);
  int changePoint();

  Program* crossover(Program *pB, int const& cpA, int const& cpB);
  void mutation(int const& type);
  void mutationChangeLeaf();
  void mutationLeaf();
  void mutationTree();

	static Program* generateRandomNodes(int maxDepth, const int& w, const int& h);
	static Program** crossover(Program* parentA, Program* parentB);

	friend std::ostream& operator<<(std::ostream &strm, const Program &p) {
		return strm << p.nodes.front();
	}
	friend std::ostream& operator<<(std::ostream &strm, const Program *p) {
		return strm << p->nodes.front();
	}

	friend bool operator<(const Program &a, const Program &b) {
		return a.fitness < b.fitness;
	}
  
  static bool compare(Program *a, Program *b){
    return a->fitness < b->fitness;
  }
};

#endif