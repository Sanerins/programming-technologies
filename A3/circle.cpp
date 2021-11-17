#include "circle.hpp"
#include <stdexcept>

#define _USE_MATH_DEFINES

#include <cmath>
#include "base-types.hpp"

kosnitskiy::Circle::Circle(const kosnitskiy::point_t &pos, double radius):
  radius_(radius),
  pos_(pos)
{
  if (radius <= 0)
  {
    throw std::invalid_argument("Incorrect radius exception");
  }
}

double kosnitskiy::Circle::getArea() const
{
  return M_PI * pow(radius_, 2);
}

kosnitskiy::rectangle_t kosnitskiy::Circle::getFrameRect() const
{
  return {2 * radius_, 2 * radius_, pos_};
}

void kosnitskiy::Circle::move(const kosnitskiy::point_t &newPos)
{
  pos_ = newPos;
}

void kosnitskiy::Circle::move(double x, double y)
{
  pos_.x += x;
  pos_.y += y;
}

void kosnitskiy::Circle::scale(double parameter)
{
  if (parameter <= 0)
  {
    throw std::invalid_argument("Wrong scaling parameter value exception");
  }
  radius_ *= parameter;
}
