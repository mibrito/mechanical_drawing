#include "gp.hpp"

GP::GP(
int const& nIndividuals,
int const& elitism,
int const& maxDepth,
double const& crossoverRate,
double const& mutationRate,
cv::Mat const& img,
int const& nThreads
)
: rand{R()},
  width{img.size[0]},
  height{img.size[1]},
  nIndividuals{nIndividuals},
  elitism{elitism},
  maxDepth{maxDepth},
  crossoverRate{crossoverRate},
  mutationRate{mutationRate},
  originalImg{img},
  nThreads{nThreads}
{}

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
void GP::calculateFitness(){
  std::thread th [nThreads];
  for(int i=0; i<nThreads; i++){
    th[i] = std::thread(
      GP::calculateFitnessFn,
      &population,
      originalImg,
      i*(population.size()/nThreads),
      ((i+1)*(population.size()/nThreads))-1
    );
  }
  for(int i=0; i<nThreads; i++){
    th[i].join();
  }
}

void GP::calculateFitnessFn(std::vector<Program*> *population, cv::Mat const& originalImg,  int begin, int const& end){
  while(begin<=end){
    (*population)[begin++]->calculateFitness(originalImg);
  }
}

void GP::sortByFitness(){
  std::sort(population.begin(), population.end(), Program::compare);
}

void GP::epoch(int const& mutationType){
	std::vector<Program*> newPopulation;

  for(int e=0; e<elitism; e++){
    newPopulation.push_back(population[e]->clone());
  }

	while(newPopulation.size() < (unsigned) nIndividuals){
		auto ind = sample(2, nIndividuals);
		
		if(rand.runif() < crossoverRate){
			auto child = Program::crossover(population[ind[0]], population[ind[1]]);

			if(rand.runif() < mutationRate){
				child[0]->mutation(mutationType);
				child[1]->mutation(mutationType);
			}
      newPopulation.push_back(child[0]);
      if(newPopulation.size() < (unsigned) nIndividuals){
        newPopulation.push_back(child[1]);
      } else {
        delete child[1];
      }
      delete [] child;
		} else {
			auto child = new Program*[2]{
				population[ind[0]]->clone(),
				population[ind[1]]->clone()
			};
			if(rand.runif() < mutationRate){
				child[0]->mutation(mutationType);
        child[1]->mutation(mutationType);
			}
      newPopulation.push_back(child[0]);
      if(newPopulation.size() < (unsigned) nIndividuals){
        newPopulation.push_back(child[1]);
      } else {
        delete child[1];
      }
      delete [] child;
		}
		delete [] ind;
	}

  for(auto p: population) delete p;
  population.clear();
	population = newPopulation;
}

void GP::run(int const& mutationType, int const& nEpoch, std::string &output) {
  generateIndividuals();
  calculateFitness();
  sortByFitness();

  int e;
  for(e=0; e<nEpoch; e++){
    epoch(mutationType);
    calculateFitness();
    sortByFitness();
    if(e%1000 == 0){
      std::cout << e << " " << population.front()->fitness - (originalImg.size[0]*population.front()->nodes.size());
      std::cout << " " << population.front()->nodes.size();
      std::cout << " " << population.back()->fitness - (originalImg.size[0]*population.back()->nodes.size());
      std::cout << " " << population.back()->nodes.size() << std::endl;
    }
    if(e%5000 == 0){
      std::string out = output+"_" +std::to_string(e) + "_" +std::to_string(population.front()->fitness - (originalImg.size[0]*population.front()->nodes.size()))+ ".jpg";
      population.front()->saveImage(out);
      out += ".prog";
      population.front()->saveProgram(out);
    }
  }
  std::cout << e << " " << population.front()->fitness - (originalImg.size[0]*population.front()->nodes.size());
  std::cout << " " << population.front()->nodes.size();
  std::cout << " " << population.back()->fitness - (originalImg.size[0]*population.back()->nodes.size());
  std::cout << " " << population.back()->nodes.size() << std::endl;

  std::string out = output+"_" +std::to_string(e) + "_" +std::to_string(population.front()->fitness - (originalImg.size[0]*population.front()->nodes.size()))+ ".jpg";
  population.front()->saveImage(out);
  out += ".prog";
  population.front()->saveProgram(out);
}

/**
 * Sample m values in a range of 0 to n-1
 * @param  m number of values to be sampled
 * @param  n upper bound of the sampling range
 * @return   array with the m values sampled
 */
int* GP::sample(const int &m, const int &n) {
	int* perm = new int [n];
	int* rtn = new int[m];
	for (int i = 0; i < n; i++) {
		perm[i] = i;
	}

	for (int i = 0; i < m; i++) {
		int r = i + (int) (rand.iunif() % (n - i));
		int t = perm[r];
		perm[r] = perm[i];
		perm[i] = t;
	}

	for(int i=0; i<m; i++){
		rtn[i] = perm[i];
	}

  delete [] perm;
	return rtn;
}
