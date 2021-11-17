#ifndef A3_RECTANGLE_HPP
#define A3_RECTANGLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

namespace kosnitskiy
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(const point_t &pos, double width, double height);

    double getArea() const override;
    rectangle_t getFrameRect() const override;

    void move(const point_t &newPos) override;
    void move(double x, double y) override;

    void scale(double parameter) override;

  private:
    double width_;
    double height_;
    point_t pos_;
  };
}

#endif //A3_RECTANGLE_HPP
