#ifndef A3_BASE_TYPES_HPP
#define A3_BASE_TYPES_HPP

namespace kosnitskiy
{
  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    double width;
    double height;
    point_t pos;
  };
}

#endif //A3_BASE_TYPES_HPP
