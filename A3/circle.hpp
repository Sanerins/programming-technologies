#ifndef A3_CIRCLE_HPP
#define A3_CIRCLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

namespace kosnitskiy
{
  class Circle: public Shape
  {
  public:
    Circle(const point_t &pos, double radius);

    double getArea() const override;
    rectangle_t getFrameRect() const override;

    void move(const point_t &newPos) override;
    void move(double x, double y) override;

    void scale(double parameter) override;

  private:
    double radius_;
    point_t pos_;
  };
}

#endif //A3_CIRCLE_HPP
