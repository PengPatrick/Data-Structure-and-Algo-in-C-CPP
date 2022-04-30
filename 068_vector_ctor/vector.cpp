#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */

Vector2D::Vector2D(): x(0), y(0){
}

Vector2D::Vector2D(double init_x, double init_y): x(init_x), y(init_y){
}

//void Vector2D::initVector(double init_x, double init_y){
//  this->x = init_x;
// this->y = init_y;
//}

double Vector2D::getMagnitude() const{
  return std::sqrt(pow(x, 2) + pow(y, 2));
}

Vector2D Vector2D::operator+(const Vector2D & rhs) const{
  Vector2D obj;
  obj.x = this->x + rhs.x;
  obj.y = this->y + rhs.y;
  return obj;
}

Vector2D & Vector2D::operator+=(const Vector2D & rhs){
  this->x += rhs.x;
  this->y += rhs.y;
  return *this;
}

double Vector2D::dot(const Vector2D & rhs) const{
  return this->x * rhs.x + this->y * rhs.y;
}

void Vector2D::print() const{
  printf("<%.2f, %.2f>", x, y);
}
