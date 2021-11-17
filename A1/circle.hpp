#ifndef A1_CIRCLE_HPP
#define A1_CIRCLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

class Circle: public Shape
{
public:
  Circle(const point_t &pos, double radius);

  double getArea() const override;

  rectangle_t getFrameRect() const override;

  void move(const point_t &) override;

  void move(double x, double y) override;
private:
  double radius_;
  point_t pos_;
};

#endif //A1_CIRCLE_HPP
