#ifndef A3_COMPOSITE_SHAPE_HPP
#define A3_COMPOSITE_SHAPE_HPP

#include <stdexcept>
#include <memory>
#include "shape.hpp"

namespace kosnitskiy
{
  struct rectangle_t;
  struct point_t;

  //The class wasn't named starting with the capital letter and the words weren't separated in the camelCase format
  //so that the exception would fit the overall code style of <stdexcept> lib
  class empty_shape: public std::exception
  {
  public:
    explicit empty_shape(const char *text):
      what_(text)
    {
    }

    const char *what() const noexcept override
    {
      return what_;
    }

  private:
    const char *what_;
  };

  class CompositeShape: public Shape
  {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape &src);
    CompositeShape(CompositeShape &&) = default;

    CompositeShape &operator=(const CompositeShape &src);
    CompositeShape &operator=(CompositeShape &&) = default;

    std::shared_ptr<Shape> operator[](int index);
    const std::shared_ptr<Shape> &operator[](int index) const;

    void add(const std::shared_ptr<Shape> &src);
    void remove(int index);

    int getSize() const;
    double getArea() const override;
    rectangle_t getFrameRect() const override;

    void move(const point_t &newPos) override;
    void move(double x, double y) override;

    void scale(double parameter) override;

  private:
    int count_;
    std::unique_ptr<std::shared_ptr<Shape>[]> shapes_;
  };
}

#endif //A3_COMPOSITE_SHAPE_HPP
