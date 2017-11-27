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
  // cv::Mat img = cv::Mat::zeros(width, height, CV_8UC1);

  draw(img);

  cv::imshow("Show Draw", img);
  cv::waitKey(0);
}

void Program::saveImage(std::string &filename){
  cv::Mat img (width, height, CV_8UC1, cv::Scalar(255));
  // cv::Mat img = cv::Mat::zeros(width, height, CV_8UC1);

  draw(img);
  cv::imwrite(filename, img);
}

void Program::saveProgram(std::string &filename){
  std::ofstream myfile;
  myfile.open (filename);
  myfile << this;
  myfile.close();
}

double Program::calculateFitness(cv::Mat const& originalImg){
  cv::Mat progImg (width, height, CV_8UC1, cv::Scalar(255));
  // cv::Mat progImg = cv::Mat::zeros(width, height, CV_8UC1);
  draw(progImg);

  cv::absdiff(originalImg, progImg, progImg);
  cv::Scalar error = cv::sum(progImg);
  fitness = (error[0]+error[1]+error[2]); ///(255*width*height);

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
  int mutationType = type;
  if(type == 3){
    mutationType = rand.mutationAll();
  } else if(type == 4) {
    mutationType = rand.mutationNTree();
  }
  switch(mutationType){
    case MUTATION_CHANGE_LEAF:
      mutationChangeLeaf();
      break;
    case MUTATION_LEAF:
      mutationLeaf();
      break;
    case MUTATION_TREE:
      mutationTree();
      break;
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

void Program::mutationLeaf(){ // leafs 2
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

        auto line = new Line(
          cv::Point(rand.x(), rand.y()),
          cv::Point(rand.x(), rand.y()),
          cv::Scalar(rand.gray()),
          rand.thickness()
          // 1
        );
        curr->drawings[i] = line;
        L.push_back(curr->drawings[i]);
      } else {
        L.push_back(curr->drawings[i]);
      }
    }

    replaceNodes.push_back(curr);
  }

  nodes = replaceNodes;
}

void Program::mutationChangeLeaf(){
  int type, x, y;
  for(unsigned i=0; i<nodes.size(); i++){
    if (Line* l = dynamic_cast<Line*>(nodes[i])){
      if(rand.runif() < 0.5){
        type = rand.mutationChangeLeaf();
        switch(type){
          case CHANGE_LEAF_P1: //leafs 1
            l->p1 = cv::Point(rand.x(), rand.y());
            break;
          case CHANGE_LEAF_P2: // leafs 1
            l->p2 = cv::Point(rand.x(), rand.y());
            break;
          case CHANGE_LEAF_H: //leafs 2
            x = rand.x();
            l->p1.x = (l->p1.x + x)%width+1;
            l->p2.x = (l->p2.x + x)%width+1;
            break;
          case CHANGE_LEAF_V: // leafs 2
            y = rand.y();
            l->p1.y = (l->p1.y + y)%height+1;
            l->p2.y = (l->p2.y + y)%height+1;
            break;
          case CHANGE_LEAF_HV: // leafs 2
            x = rand.x();
            l->p1.x = (l->p1.x + x)%width+1;
            l->p2.x = (l->p2.x + x)%width+1;

            y = rand.y();
            l->p1.y = (l->p1.y + y)%height+1;
            l->p2.y = (l->p2.y + y)%height+1;
            break;
          case CHANGE_LEAF_R: // leafs 3
            x = rand.x();
            l->p1.x = (l->p1.x + x)%width+1;
            l->p2.x = (l->p2.x - x)%width+1;
            break;
          case CHANGE_LEAF_COLOR: // leafs1
            l->color = cv::Scalar(rand.gray());
            break;
          case CHANGE_LEAF_THICK: // leafs 3
            l->thickness = rand.thickness();
            break;
        }
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
