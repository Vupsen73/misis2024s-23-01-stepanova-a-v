#include <iostream>
#include <vector>
#include <string>

double x = 0;
double y = 0;

class Go 
{
public:
  virtual void Move() {};

  double mv = 0.0;
};

class GoN : public Go
{
public:
  void Move() {
    y += mv;
  }
};

class GoE : public Go
{
public:
  void Move() {
    x += mv;
  }
};

class GoS : public Go
{
public:
  void Move() {
    y -= mv;
  }
};

class GoW : public Go
{
public:
  void Move() {
    x -= mv;
  }
};

void RE(std::vector<Go*>& vec, int n) {
  for (int i = 0; i < n; i++) {
    vec.pop_back();
  }
}

void GO(std::vector<Go*>& vec, double new_x, double new_y) {
  x = new_x;
  y = new_y;
  for (auto i : vec) {
    i->Move();
  }

  std::cout << x << " " << y << std::endl;

  vec.clear();
}

int main() {
  
  std::vector<Go*> vec;

  int t = 0;
  std::cin >> t;
  for (int i = 0; i < t; i++) {
    std::string type;
    std::cin >> type;

    if (type == "RE") {
      int n = 0;
      std::cin >> n;
      RE(vec, n);
    }
    if (type == "GO") {
      int new_x = 0;
      int new_y = 0;
      std::cin >> new_x >> new_y;
      GO(vec, new_x, new_y);
    }
    if (type == "GN") {
      double mv = 0.;
      std::cin >> mv;
      Go* nw = new GoN;
      nw->mv = mv;
      vec.push_back(nw);
    }
    if (type == "GE") {
      double mv = 0.;
      std::cin >> mv;
      Go* nw = new GoE;
      nw->mv = mv;
      vec.push_back(nw);
    }
    if (type == "GS") {
      double mv = 0.;
      std::cin >> mv;
      Go* nw = new GoS;
      nw->mv = mv;
      vec.push_back(nw);
    }
    if (type == "GW") {
      double mv = 0.;
      std::cin >> mv;
      Go* nw = new GoW;
      nw->mv = mv;
      vec.push_back(nw);
    }
  }

  return 0;
}