#ifndef B5_SHAPE_HPP
#define B5_SHAPE_HPP

#include <vector>
#include <iosfwd>

namespace kosnitskiy
{
  class Shape
  {
  public:
    struct Point
    {
      int x;
      int y;
      friend std::istream &operator>>(std::istream &in, Point &point);
      friend std::ostream &operator<<(std::ostream &out, const Point &point);
    };

    const std::vector<Point> &getPoints();

    friend std::ostream &operator<<(std::ostream &out, const Shape &shape);

    friend std::istream &operator>>(std::istream &in, Shape &shape);

    size_t size();

  private:
    std::vector<Point> points;
  };

  std::istream &operator>>(std::istream &in, Shape::Point &point);
  std::ostream &operator<<(std::ostream &out, const Shape::Point &point);
  std::ostream &operator<<(std::ostream &out, const Shape &shape);
  std::istream &operator>>(std::istream &in, Shape &shape);
}

#endif //B5_SHAPE_HPP
