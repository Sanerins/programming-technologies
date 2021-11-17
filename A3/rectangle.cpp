#include "rectangle.hpp"
#include <stdexcept>
#include "base-types.hpp"

kosnitskiy::Rectangle::Rectangle(const kosnitskiy::point_t &pos, double width, double height):
  width_(width),
  height_(height),
  pos_(pos)
{
  if ((width <= 0) && (height <= 0))
  {
    throw std::invalid_argument("Incorrect measures exception");
  }
  else if (width <= 0)
  {
    throw std::invalid_argument("Incorrect width exception");
  }
  else if (height <= 0)
  {
    throw std::invalid_argument("Incorrect height exception");
  }
}

double kosnitskiy::Rectangle::getArea() const
{
  return width_ * height_;
}

kosnitskiy::rectangle_t kosnitskiy::Rectangle::getFrameRect() const
{
  return {width_, height_, pos_};
}

void kosnitskiy::Rectangle::move(const kosnitskiy::point_t &newPos)
{
  pos_ = newPos;
}

void kosnitskiy::Rectangle::move(double x, double y)
{
  pos_.x += x;
  pos_.y += y;
}

void kosnitskiy::Rectangle::scale(double parameter)
{
  if (parameter <= 0)
  {
    throw std::invalid_argument("Wrong scaling parameter value exception");
  }
  width_ *= parameter;
  height_ *= parameter;
}
