/**
 * Todas as tarefas deste exercicio devem ser feitas sobre esse arquivo.
 * Os metodos e operacoes marcados com a tag "TODO" devem ser editados.
 */

#include <iostream>
#include "polygon.h"

#include <algorithm>

std::ostream& operator << (std::ostream &out, const Polygon &poly) {
  for (const Point& p: poly.limits) {
    out << " " << p;
  }
  return out;
}

bool operator == (const Polygon &lhs, const Polygon &rhs) {
  std::vector<Point> left = (const std::vector<Point>&)lhs;
  std::vector<Point> right = (const std::vector<Point>&)rhs;

  if(left.size() != right.size())
    return false;

  if(left.size() == 1 && right.size() == 1) {
    if(left[0].contains(right[0]))
      return true;
    else
      return false;
  }

  int left_start_x = std::min(left[0].x, left[1].x);
  int left_limit_x = std::max(left[0].x, left[1].x);

  int left_start_y = std::min(left[0].y, left[1].y);
  int left_limit_y = std::max(left[0].y, left[1].y);

  int right_start_x = std::min(right[0].x, right[1].x);
  int right_limit_x = std::max(right[0].x, right[1].x);

  int right_start_y = std::min(right[0].y, right[1].y);
  int right_limit_y = std::max(right[0].y, right[1].y);

  if(left_start_x == right_start_x && left_limit_x == right_limit_x) {
    if(left_start_y == right_start_y && left_limit_y == right_limit_y) {
      return true;
    }
  }

  return false;
}

bool Point::contains(const Point& p) const {
  return p.x == this->x && p.y == this->y;
}

std::ostream& operator << (std::ostream &out, const Point &p) {
  out << "(" << p.x << ", " << p.y << ")";
  return out;
}

bool RightRectangle::contains(const Point& p) const {
  int x_start, y_start, x_limit, y_limit;

  Point p0 = limits[0];
  Point p1 = limits[1];

  x_start = std::min(p0.x, p1.x);
  y_start = std::min(p0.y, p1.y);

  x_limit = std::max(p0.x, p1.x);
  y_limit = std::max(p0.y, p1.y);

  if(p.x >= x_start && p.x <= x_limit) {
    if(p.y >= y_start && p.y <= y_limit) {
      return true;
    }
  }

  return false;
}

Point::Point(int xx, int yy): x(xx), y(yy) {
  limits.push_back(*this);
}

RightRectangle::RightRectangle(int x0, int y0, int x1, int y1) {
  Point p0 = Point(x0, y0);
  Point p1 = Point(x1, y1);

  limits.push_back(p0);
  limits.push_back(p1);
}