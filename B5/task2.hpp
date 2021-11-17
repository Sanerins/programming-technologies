#ifndef B5_TASK2_HPP
#define B5_TASK2_HPP

#include <iosfwd>
#include <list>
#include "shape.hpp"

namespace kosnitskiy
{
  void executeSecondTask(std::istream &in, std::ostream &out);

  void readShapes(std::istream &in, std::list<Shape> &shapes);

  bool isRectangle(Shape &shape);

  bool isSquare(Shape &shape);

  bool isDot(Shape &shape);

  bool isLine(Shape &shape);

}

#endif //B5_TASK2_HPP
