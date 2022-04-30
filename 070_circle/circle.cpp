#include "circle.hpp"
#include <cmath>
#include <cstdlib>

using namespace std;

Circle::Circle(Point p, double r):center(p),radius(r){}

void Circle::move(double dx, double dy){
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle){
  double r1 = radius;
  double r2 = otherCircle.radius;
  double d = center.distanceFrom(otherCircle.center);

  if(r1 == 0 || r2 == 0 || d >= r1 + r2){
    return 0;
  }
  if(d <= r1 - r2 || d <= r2 - r1){
    return r2 < r1 ? M_PI*r2*r2 : M_PI*r1*r1;
  }

  double cos1 = (d*d + r1*r1 - r2*r2)/(2*r1*d);
  double cos2 = (d*d + r2*r2 - r1*r1)/(2*r2*d);
  double h = r2*sqrt(1 - cos2*cos2);

  double rectanS = d*h/2;
  double fan1S = acos(cos1)*r1*r1/2;
  double fan2S = acos(cos2)*r2*r2/2;

  return 2*(fan1S + fan2S - rectanS);
}

