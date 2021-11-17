#ifndef A3_SHAPE_HPP
#define A3_SHAPE_HPP

namespace kosnitskiy
{
  struct rectangle_t;
  struct point_t;

  class Shape
  {
  public:
    virtual ~Shape() = default;

    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;

    virtual void move(const point_t &point) = 0;
    virtual void move(double x, double y) = 0;

    virtual void scale(double parameter) = 0;
  };
}

#endif //A3_SHAPE_HPP
