#include "primitives.hpp"

/**
 * Draw functions
 */
Draw::Draw (const Draw &d) {
  depth = d.depth;
}

Draw::Draw (int d) {
  depth = d;
}

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

void Draw::draw(cv::Mat img) const {
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

/**
 * Line funcions
 */

Line::Line(const Line &l)
: Draw (0){
  p1 = l.p1;
  p2 = l.p2;
  color = l.color;
}

Line::Line (cv::Point p1, cv::Point p2, cv::Scalar color)
: Draw (0) {
  this->p1 = p1;
  this->p2 = p2;
  this->color = color;
}

Line* Line::clone() const {
  return new Line(*this);
}

void Line::print(std::ostream& out) const {
  out << std::endl << "\t" << "Line( " << p1 << "," << p2 << "," << color << " )";
}

void Line::draw(cv::Mat img) const {
  cv::line(img, p1, p2, color, 1, CV_AA);
}

bool Line::equals(const Draw &d) const {
  if (auto const& l = dynamic_cast<const Line*>(&d)){
    return (p1 == l->p1) && (p2 == l->p2) && (color == l->color);
  } else {
    return false;
  }
}

Line* Line::generateRandom(int width, int height) {
  return new Line(
    cv::Point(RANDINT(width-1), RANDINT(height-1)),
    cv::Point(RANDINT(width-1), RANDINT(height-1)),
    cv::Scalar(RANDINT(MAX_GRAY))
  );
}