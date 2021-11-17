#ifndef A1_RECTANGLE_HPP
#define A1_RECTANGLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

class Rectangle: public Shape
{
public:
  Rectangle(const point_t &pos, double width, double height);

  double getArea() const override;

  rectangle_t getFrameRect() const override;

  void move(const point_t &) override;

  void move(double x, double y) override;
private:
  double width_;
  double height_;
  point_t pos_;
};

#endif //A1_RECTANGLE_HPP
