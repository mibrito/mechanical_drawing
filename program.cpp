#include "program.hpp"

Program::Program(const Program &p){
  width = p.width;
  height = p.height;
}

Program::Program(int w, int h){
  width = w;
  height = h;
}

Program::~Program(){
  delete nodes.front();
  // delete nodes.back();
  nodes.clear();
}

Program* Program::clone() const {
  return new Program( *this );
}

void Program::draw(cv::Mat img){
  nodes.front()->draw(img);
}

cv::Scalar Program::calculateFitness(cv::Mat originalImg){
  cv::Mat progImg = cv::Mat::zeros(originalImg.size[0], originalImg.size[1], CV_8UC1);
  cv::Mat tmp;

  draw(progImg);

  cv::absdiff(originalImg, progImg, tmp);
  tmp.convertTo(tmp, CV_32F);
  tmp = tmp.mul(tmp);
  cv::sqrt(cv::mean(tmp), fitness);

  // cv::imshow("Show Draw", tmp);
  // cv::waitKey(0);

  return fitness;
}

int Program::crossoverPoint(){
  return (std::rand() % nodes.size()-2)+1;
}

void Program::fillRandomNodes(int maxDepth) {
  auto root = new Draw(0);
  nodes.push_back(root);

  std::list<Draw*> L;
  L.push_back(root);
	while(!L.empty()){
    auto curr = L.front();
    L.pop_front();

    if(curr->depth == maxDepth || std::rand()%2 > 0) {
      for(int i=0; i < MAX_PRIMITIVES; i++){
        auto child = Line::generateRandom(width, height);
        curr->drawings.push_back(child);
        nodes.push_back(child);
      }
    } else {
      for(int i=0; i < MAX_DRAWS; i++){
        auto child = new Draw(curr->depth+1);

        curr->drawings.push_back(child);
        nodes.push_back(child);
        L.push_back(child);
      }
    }
	}
}

Program* Program::generateRandomNodes(int maxDepth, const int& w, const int& h){
  Program* p = new Program(w, h);
  p->fillRandomNodes(maxDepth);
  return p;
}

// change from static...

Program** Program::crossover(Program *parentA, Program *parentB){
  int cpA = parentA->crossoverPoint();
  int cpB = parentB->crossoverPoint();

  // std::cout << "cpA" << std::endl;
  std::cout << parentA->nodes[cpA] << std::endl;
  // std::cout << "cpB" << std::endl;
  // std::cout << parentB->nodes[cpB] << std::endl;
  std::cout << "A" << std::endl;
  std::cout << parentA << std::endl;
  // std::cout << "B" << std::endl;
  // std::cout << parentB << std::endl;

  Program** rtn = new Program*[2]{new Program(*parentA)}; // = new Program*[2];

  rtn[0]->nodes.push_back(parentA->nodes.front()->clone());

  // crossover of draw rtn[0] = pA->crossover(pB, cpA, cpB)
  std::list<Draw*> L;
  L.push_back(rtn[0]->nodes.back());
  while(!L.empty()){
    Draw* curr = L.front();
    L.pop_front();

    for(unsigned i=0; i<curr->drawings.size(); i++){
      if(curr->drawings[i]->equals(*parentA->nodes[cpA])){
        delete curr->drawings[i];
        curr->drawings[i] = parentB->nodes[cpB]->clone();
        L.push_back(curr->drawings[i]);
      } else {
        L.push_back(curr->drawings[i]);
      }
    }

    rtn[0]->nodes.push_back(curr);
  }

  std::cout << "rtnA" << std::endl;
  std::cout << rtn[0] << std::endl;
  std::cout << parentA << std::endl;
  // std::cout << "rtnB" << std::endl;
  // std::cout << rtn[1] << std::endl;

  return rtn;
}