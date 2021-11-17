#include "composite-shape.hpp"
#include <memory>
#include <stdexcept>
#include "shape.hpp"
#include "base-types.hpp"

kosnitskiy::CompositeShape::CompositeShape():
  count_(0),
  shapes_(std::make_unique<std::shared_ptr<Shape>[]>(0))
{}

kosnitskiy::CompositeShape::CompositeShape(const kosnitskiy::CompositeShape &src):
  count_(src.count_),
  shapes_(std::make_unique<std::shared_ptr<Shape>[]>(src.count_))
{
  for (int i = 0; i < src.count_; i++)
  {
    shapes_[i] = src.shapes_[i];
  }
}

kosnitskiy::CompositeShape &kosnitskiy::CompositeShape::operator=(const kosnitskiy::CompositeShape &src)
{
  if (this != &src)
  {
    CompositeShape temp(src);
    std::swap(shapes_, temp.shapes_);
    std::swap(count_, temp.count_);
  }

  return *this;
}

std::shared_ptr<kosnitskiy::Shape> kosnitskiy::CompositeShape::operator[](int index)
{
  if ((index < 0) || (index >= count_))
  {
    throw std::invalid_argument("Inaccessible argument exception");
  }

  return shapes_[index];
}

const std::shared_ptr<kosnitskiy::Shape> &kosnitskiy::CompositeShape::operator[](int index) const
{
  if ((index < 0) || (index >= count_))
  {
    throw std::invalid_argument("Inaccessible argument exception");
  }

  return shapes_[index];
}

void kosnitskiy::CompositeShape::add(const std::shared_ptr<Shape> &src)
{
  if (!src || (this == src.get()))
  {
    throw std::invalid_argument("Attempt to add an invalid argument exception");
  }

  std::unique_ptr<std::shared_ptr<Shape>[]> shapes(new std::shared_ptr<Shape>[count_ + 1]);

  for (int i = 0; i < count_; i++)
  {
    shapes[i] = std::move(shapes_[i]);
  }
  shapes[count_] = src;

  count_++;
  shapes_ = std::move(shapes);
}

void kosnitskiy::CompositeShape::remove(int index)
{
  if ((index < 0) || (index >= count_))
  {
    throw std::invalid_argument("Inaccessible argument exception");
  }

  std::unique_ptr<std::shared_ptr<Shape>[]> shapes(new std::shared_ptr<Shape>[count_ - 1]);

  for (int i = 0; i < index; i++)
  {
    shapes[i] = shapes_[i];
  }
  for (int i = index + 1; i < count_; i++)
  {
    shapes[i - 1] = shapes_[i];
  }

  count_--;
  shapes_ = std::move(shapes);
}

int kosnitskiy::CompositeShape::getSize() const
{
  return count_;
}

double kosnitskiy::CompositeShape::getArea() const
{
  double area = 0.0;

  for (int i = 0; i < count_; i++)
  {
    area += shapes_[i]->getArea();
  }

  return area;
}

kosnitskiy::rectangle_t kosnitskiy::CompositeShape::getFrameRect() const
{
  if (count_ == 0)
  {
    throw kosnitskiy::empty_shape("Attempt to get a frame of an empty composite shape exception");
  }

  bool isShallow = true;
  int numberOfEmpty = 0;
  double bottomLeftX = 0.0;
  double bottomLeftY = 0.0;
  double upperRightX = 0.0;
  double upperRightY = 0.0;

  for (int i = 0; i < count_; i++)
  {
    try
    {
      if (isShallow)
      {
        rectangle_t temp = shapes_[i]->getFrameRect();
        isShallow = false;
        bottomLeftX = temp.pos.x - (temp.width / 2);
        bottomLeftY = temp.pos.y - (temp.height / 2);
        upperRightX = temp.pos.x + (temp.width / 2);
        upperRightY = temp.pos.y + (temp.height / 2);
      }
      else
      {
        rectangle_t temp = shapes_[i]->getFrameRect();

        if (temp.pos.x + (temp.width / 2.0) > upperRightX)
        {
          upperRightX = temp.pos.x + (temp.width / 2.0);
        }
        if (temp.pos.y + (temp.height / 2.0) > upperRightY)
        {
          upperRightY = temp.pos.y + (temp.height / 2.0);
        }
        if (temp.pos.x - (temp.width / 2.0) < bottomLeftX)
        {
          bottomLeftX = temp.pos.x - (temp.width / 2.0);
        }
        if (temp.pos.y - (temp.height / 2.0) < bottomLeftY)
        {
          bottomLeftY = temp.pos.y - (temp.height / 2.0);
        }
      }
    }
    catch (const kosnitskiy::empty_shape &exception)
    {
      numberOfEmpty++;
    }
  }
  if (isShallow)
  {
    throw kosnitskiy::empty_shape("Attempt to get a frame of an empty composite shape exception");
  }
  return {upperRightX - bottomLeftX, upperRightY - bottomLeftY,
           {(upperRightX + bottomLeftX) / 2.0, (upperRightY + bottomLeftY) / 2.0}};
}

void kosnitskiy::CompositeShape::move(const kosnitskiy::point_t &newPos)
{
  point_t oldPos{0, 0};

  try
  {
    oldPos = getFrameRect().pos;
  }
  catch (const kosnitskiy::empty_shape &exception)
  {
    return;
  }

  move(newPos.x - oldPos.x, newPos.y - oldPos.y);
}

void kosnitskiy::CompositeShape::move(double x, double y)
{
  for (int i = 0; i < count_; i++)
  {
    shapes_[i]->move(x, y);
  }
}

void kosnitskiy::CompositeShape::scale(double parameter)
{
  if ((parameter > 0.0) && (count_ > 0))
  {
    point_t pos{0, 0};

    try
    {
      pos = getFrameRect().pos;
    }
    catch (const kosnitskiy::empty_shape &exception)
    {
      return;
    }

    for (int i = 0; i < count_; i++)
    {
      point_t shapePos{0, 0};

      try
      {
        shapePos = shapes_[i]->getFrameRect().pos;
      }
      catch (const kosnitskiy::empty_shape &exception)
      {
        continue;
      }

      shapes_[i]->scale(parameter);
      shapes_[i]->move((shapePos.x - pos.x) * parameter - (shapePos.x - pos.x),
                         (shapePos.y - pos.y) * parameter - (shapePos.y - pos.y));
    }
  }
  else if (parameter <= 0.0)
  {
    throw std::invalid_argument("Wrong scaling parameter value exception");
  }
}
