#include "circle.hpp"
#include <stdexcept>

#define _USE_MATH_DEFINES

#include <cmath>
#include "base-types.hpp"

Circle::Circle(const point_t &pos, double radius):
  radius_(radius),
  pos_(pos)
{
  if (radius <= 0)
  {
    throw std::invalid_argument("\nIncorrect radius exception\n");
  }
}

double Circle::getArea() const
{
  return M_PI * pow(radius_, 2);
}

rectangle_t Circle::getFrameRect() const
{
  return {2 * radius_, 2 * radius_, pos_};
}

void Circle::move(const point_t &newPos)
{
  pos_ = newPos;
}

void Circle::move(double x, double y)
{
  pos_.x += x;
  pos_.y += y;
}
