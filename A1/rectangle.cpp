#include "rectangle.hpp"
#include <stdexcept>
#include "base-types.hpp"

Rectangle::Rectangle(const point_t &pos, double width, double height):
  width_(width),
  height_(height),
  pos_(pos)
{
  if ((width <= 0) && (height <= 0))
  {
    throw std::invalid_argument("\nIncorrect measures exception\n");
  }
  else if (width <= 0)
  {
    throw std::invalid_argument("\nIncorrect width exception\n");
  }
  else if (height <= 0)
  {
    throw std::invalid_argument("\nIncorrect height exception\n");
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {width_, height_, pos_};
}

void Rectangle::move(const point_t &newPos)
{
  pos_ = newPos;
}

void Rectangle::move(double x, double y)
{
  pos_.x += x;
  pos_.y += y;
}
