#ifndef __PROGRAM_H_INCLUDED__
#define __PROGRAM_H_INCLUDED__

#include <vector>
#include <list>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <opencv2/core.hpp>
#include "primitives.hpp"

#define MAX_DRAWS 2
#define MAX_PRIMITIVES 4

class Program {
public:
	int width, height;

	cv::Scalar fitness = cv::Scalar(std::numeric_limits<float>::max());
	std::vector<Draw*> nodes;

	explicit Program(const Program &p);
	Program(int width,int height);
	virtual ~Program();

	void draw(cv::Mat img);
	cv::Scalar calculateFitness(cv::Mat originalImg);
	void fillRandomNodes(int maxDepth);
	int crossoverPoint();

	virtual Program* clone() const;


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

};

#endif