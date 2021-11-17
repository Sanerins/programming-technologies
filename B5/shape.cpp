#include "shape.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>
#include "utils.hpp"

const std::vector<kosnitskiy::Shape::Point> &kosnitskiy::Shape::getPoints()
{
  return points;
}

size_t kosnitskiy::Shape::size()
{
  return points.size();
}

std::ostream &kosnitskiy::operator<<(std::ostream &out, const kosnitskiy::Shape &shape)
{
  out << shape.points.size();
  for (auto point: shape.points)
  {
    out << ' ' << point;
  }
  return out;
}

std::istream &kosnitskiy::operator>>(std::istream &in, kosnitskiy::Shape::Point &point)
{
  in >> kosnitskiy::eatWhiteSpaces;
  char leftBracket = ' ';
  char rightBracket = ' ';
  char delimiter = ' ';
  in >> std::noskipws >> kosnitskiy::eatWhiteSpaces >> leftBracket >> kosnitskiy::eatWhiteSpaces >> point.x >> kosnitskiy::eatWhiteSpaces
     >> delimiter >> kosnitskiy::eatWhiteSpaces >> point.y >> kosnitskiy::eatWhiteSpaces >> rightBracket;
  if ((in.fail()) || leftBracket != '(' || rightBracket != ')' || delimiter != ';')
  {
    in.clear();
    in.setstate(std::ios::failbit);
    return in;
  }
  return in;
}

std::ostream &kosnitskiy::operator<<(std::ostream &out, const kosnitskiy::Shape::Point &point)
{
  out << "(" << point.x << "; " << point.y << ")";
  return out;
}

std::istream &kosnitskiy::operator>>(std::istream &in, kosnitskiy::Shape &shape)
{
  in >> eatNewLines;
  if (in.fail())
  {
    return in;
  }
  int size;
  in >> size;
  if (in.fail())
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  Shape tempShape;
  std::copy_n(std::istream_iterator<kosnitskiy::Shape::Point>(in), size, std::back_inserter(tempShape.points));
  if (in.fail() && !in.eof())
  {
    return in;
  }
  shape = std::move(tempShape);
  return in;
}
