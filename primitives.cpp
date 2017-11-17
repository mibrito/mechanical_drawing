#include "random.hpp"
#include "primitives.hpp"

/**
 * Draw functions
 */
Draw::Draw (const Draw &d)
: depth{d.depth}
{}

Draw::Draw (int d)
: depth{d}
{}

Draw::~Draw(){
  for(Draw *d: drawings){
    delete d;
  }
  drawings.clear();
}

Draw* Draw::clone() const {
  auto d = new Draw(*this);
  for(auto const &c: this->drawings){
    d->drawings.push_back(c->clone());
  }
  return d;
}

void Draw::print(std::ostream& out) const {
  out << std::endl;
  for(int i=0; i<depth; i++) out << "\t";

  out << "Draw" << depth << "( ";
  for(auto const& c: drawings){
    out << c;
  }
  out << std::endl;
  for(int i=0; i<depth; i++) out << "\t";
  out << ")" << std::endl;
};

void Draw::draw(cv::Mat const& img) const {
  for(auto const& c: drawings){
    c->draw(img);
  }
}

bool Draw::equals(const Draw &d) const {
  if (depth != d.depth) return false;
  if (drawings.size() != d.drawings.size()) return false;

  for(unsigned i=0; i<drawings.size(); i++){
    if(drawings[i] != d.drawings[i]) return false;
  }

  return true;
}

std::vector<Draw*> Draw::generate(int const& maxDepth, int const& w, int const& h){
  R rand = R(w, h);
  std::vector<Draw*> nodes;

  auto root = new Draw(0);
  nodes.push_back(root);

  std::list<Draw*> L;
  L.push_back(root);
  while(!L.empty()){
    auto curr = L.front();
    L.pop_front();

    if(curr->depth == maxDepth || rand.runif() > 0.5) {
      for(int i=0; i < MAX_PRIMITIVES; i++){
        auto child = new Line(
          cv::Point(rand.x(), rand.y()),
          cv::Point(rand.x(), rand.y()),
          cv::Scalar(rand.gray()),
          // rand.thickness()
          1
        );
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

  return nodes;
}


/**
 * Line funcions
 */

Line::Line(const Line &l)
: Draw (0), p1{l.p1}, p2{l.p2}, color{l.color}, thickness{l.thickness}
{}

Line::Line (cv::Point const& p1, cv::Point const& p2, cv::Scalar const& color, int const& thickness)
: Draw (0), p1{p1}, p2{p2}, color{color}, thickness{thickness}
{}

Line* Line::clone() const {
  return new Line(*this);
}

void Line::print(std::ostream& out) const {
  out << "Line( " << p1 << "," << p2 << "," << color << " )";
}

void Line::draw(cv::Mat const& img) const {
  cv::line(img, p1, p2, color, thickness, CV_AA);
}

bool Line::equals(const Draw &d) const {
  if (auto const& l = dynamic_cast<const Line*>(&d)){
    return (p1 == l->p1) && (p2 == l->p2) && (color == l->color);
  } else {
    return false;
  }
}

/**
 * Triangle functions
 */

// Triangle::Triangle(const Triangle &l)
// : Draw (0), p1{l.p1}, p2{l.p2}, p3{l.p3}, color{l.color}
// {}

// Triangle::Triangle (cv::Point const& p1, cv::Point const& p2, cv::Point const& p3, cv::Scalar const& color)
// : Draw (0), p1{p1}, p2{p2}, p3{p3}, color{color}
// {}

// Triangle* Triangle::clone() const {
//   return new Triangle(*this);
// }

// void Triangle::print(std::ostream& out) const {
//   out << "Triangle( " << p1 << "," << p2 << "," << p3 << "," << color << " )";
// }

// void Triangle::draw(cv::Mat const& img) const {
//   cv::line(img, p1, p2, color, thickness, CV_AA);
// }

// bool Triangle::equals(const Draw &d) const {
//   if (auto const& l = dynamic_cast<const Triangle*>(&d)){
//     return (p1 == l->p1) && (p2 == l->p2) && (color == l->color);
//   } else {
//     return false;
//   }
// }