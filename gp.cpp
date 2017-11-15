#include "gp.hpp"

GP::GP(const int &nIndividuals, const int &maxDepth, const int &width, const int &height){
	this->nIndividuals = nIndividuals;
	this->maxDepth = maxDepth;
	this->width = width;
	this->height = height;

	generateIndividuals();
}

GP::~GP(){
	while(!population.empty()){
		Program* ind = population.back();
		population.pop_back();
		delete ind;
	}
}

/**
 * Generate program nIndividuals to compose the population
 */
void GP::generateIndividuals() {
	for(int i=0; i<nIndividuals; i++){
		population.push_back(Program::generateRandomNodes(maxDepth, width, height));
	}
}

/**
 * Call calculateFitness for each program among population
 */
void GP::calculateFitness(cv::Mat originalImg){
	for (Program* p: population){
		p->calculateFitness(originalImg);
	}
}

/**
 * Sample m values in a range of 0 to n-1
 * @param  m number of values to be sampled
 * @param  n upper bound of the sampling range
 * @return   array with the m values sampled
 */
int* GP::sample(const int &m, const int &n) {
	int perm [n] = {};
	int* rtn = new int(m);
	for (int i = 0; i < n; i++) {
		perm[i] = i;
	}

	for (int i = 0; i < m; i++) {
		int r = i + (int) (std::rand() % (n - i));
		int t = perm[r];
		perm[r] = perm[i];
		perm[i] = t;
	}

	for(int i=0; i<m; i++){
		rtn[i] = perm[i];
	}

	return rtn;
}