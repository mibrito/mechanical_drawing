#include "program.hpp"


Program::Program(const Program &p)
: rand{R(p.width, p.height)}, width{p.width}, height{p.height}
{}

Program::Program(int const& w, int const& h)
: rand{R(w, h)}, width{w}, height{h}
{}

Program::~Program(){
  delete nodes.front();
  nodes.clear();
}

Program* Program::clone() const {
  auto pr = new Program(*this);

  std::list<Draw*> L;
  L.push_back(nodes.front()->clone());
  while(!L.empty()){
    Draw* curr = L.front();
    L.pop_front();

    for(unsigned i=0; i<curr->drawings.size(); i++){
      L.push_back(curr->drawings[i]);
    }

    pr->nodes.push_back(curr);
  }

  return pr;
}

void Program::draw(cv::Mat const& img){
  nodes.front()->draw(img);
}

void Program::show() {
  cv::Mat img (width, height, CV_8UC1, cv::Scalar(255));

  draw(img);

  cv::imshow("Show Draw", img);
  cv::waitKey(0);
}

void Program::saveImage(const char* filename){
  cv::Mat img (width, height, CV_8UC1, cv::Scalar(255));

  draw(img);
  cv::imwrite(filename, img);
}

void Program::saveProgram(const char* filename){
  std::ofstream myfile;
  myfile.open (filename);
  myfile << this;
  myfile.close();
}

cv::Scalar Program::calculateFitness(cv::Mat const& originalImg){
  cv::Mat progImg = cv::Mat::zeros(originalImg.size[0], originalImg.size[1], CV_8UC1);
  cv::Mat tmp;

  draw(progImg);

  cv::absdiff(originalImg, progImg, tmp);
  tmp.convertTo(tmp, CV_32F);
  tmp = tmp.mul(tmp);
  cv::sqrt(cv::mean(tmp), fitness);

  return fitness;
}

int Program::changePoint(){
  return (rand.iunif() % (nodes.size()-2))+1;
}

void Program::fillRandomNodes(int maxDepth) {
  nodes = Draw::generate(maxDepth, width, height); 
}

Program* Program::generateRandomNodes(int maxDepth, const int& w, const int& h){
  Program* p = new Program(w, h);
  p->fillRandomNodes(maxDepth);
  return p;
}

Program* Program::crossover(Program *pB, int const& cpA, int const& cpB){
  Draw* crossoverPoint = nodes[cpA];
  Program* child = new Program(*this);
  
  std::list<Draw*> L;
  L.push_back(nodes.front()->clone());
  while(!L.empty()){
    Draw* curr = L.front();
    L.pop_front();

    for(unsigned i=0; i<curr->drawings.size(); i++){
      if(crossoverPoint != NULL && curr->drawings[i]->equals(*crossoverPoint)){
        delete curr->drawings[i];
        crossoverPoint = NULL;
        curr->drawings[i] = pB->nodes[cpB]->clone();
        L.push_back(curr->drawings[i]);
      } else {
        L.push_back(curr->drawings[i]);
      }
    }

    child->nodes.push_back(curr);
  }

  return child;
}

void Program::mutation(int const& type){
  switch(type){
    case MUTATION_LEAF:
      mutationLeaf();
      break;
    case MUTATION_TREE:
      mutationTree();
      break;
    default:
      if(rand.runif() < 0.5){
        mutationLeaf();
      } else {
        mutationTree();
      }
  }
}

void Program::mutationTree(){
  int m = changePoint();

  Draw* mutationPoint = nodes[m];

  std::vector<Draw*> replaceNodes;

  std::list<Draw*> L;
  L.push_back(nodes.front());
  while(!L.empty()){
    Draw* curr = L.front();
    L.pop_front();

    for(unsigned i=0; i<curr->drawings.size(); i++){
      if(mutationPoint != NULL && curr->drawings[i] == mutationPoint){
        delete curr->drawings[i];
        mutationPoint = NULL;

        auto newNodes = Draw::generate(MAX_MUTATION_DEPTH, width, height);
        curr->drawings[i] = newNodes.front();
        L.push_back(curr->drawings[i]);
      } else {
        L.push_back(curr->drawings[i]);
      }
    }

    replaceNodes.push_back(curr);
  }

  nodes = replaceNodes;
}

void Program::mutationLeaf(){
  for(unsigned i=0; i<nodes.size(); i++){
    if (Line* l = dynamic_cast<Line*>(nodes[i])){
      if(rand.runif() < 0.5){
        if(rand.runif() < 0.5){
          l->p2 = cv::Point(rand.x(), rand.y());
        } else if(rand.runif() < 0.5) {
          l->p2 = cv::Point(rand.x(), rand.y());
        } else {
          l->color = cv::Scalar(rand.gray());
        }
        //  else if(rand.runif() < 0.5) {
        //   l->thickness = rand.thickness();
        // }  
        break;
      }
    }
  }
}

// change from static...

Program** Program::crossover(Program *parentA, Program *parentB){
  int cpA = parentA->changePoint();
  int cpB = parentB->changePoint();

  auto rtn = new Program*[2]{
    parentA->crossover(parentB, cpA, cpB),
    parentB->crossover(parentA, cpB, cpA)
  };

  return rtn;
}