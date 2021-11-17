#include "task2.hpp"
#include <iostream>
#include <list>
#include <iterator>
#include "shape.hpp"
#include "utils.hpp"

void kosnitskiy::executeSecondTask(std::istream &in, std::ostream &out)
{
  std::list<kosnitskiy::Shape> shapes;
  kosnitskiy::readShapes(in, shapes);
  std::list<kosnitskiy::Shape::Point> points;

  size_t verticesCount = 0;
  int triangleCount = 0;
  std::list<kosnitskiy::Shape> triangles;
  int squareCount = 0;
  std::list<kosnitskiy::Shape> squares;
  int rectangleCount = 0;
  std::list<kosnitskiy::Shape> rectangles;
  for (auto shape = shapes.begin(); shape != shapes.end();)
  {
    verticesCount += shape->size();
    if (shape->size() == 3)
    {
      points.push_back(*shape->getPoints().begin());
      triangleCount++;
      triangles.push_back(*shape);
      shape = shapes.erase(shape);
    }
    else if (kosnitskiy::isSquare(*shape))
    {
      points.push_back(*shape->getPoints().begin());
      squareCount++;
      rectangleCount++;
      squares.push_back(*shape);
      shape = shapes.erase(shape);
    }
    else if (kosnitskiy::isRectangle(*shape) || kosnitskiy::isLine(*shape))
    {
      points.push_back(*shape->getPoints().begin());
      rectangleCount++;
      rectangles.push_back(*shape);
      shape = shapes.erase(shape);
    }
    else if (shape->size() == 5)
    {
      shape = shapes.erase(shape);
    }
    else
    {
      points.push_back(*shape->getPoints().begin());
      shape++;
    }
  }
  shapes.splice(shapes.begin(), rectangles);
  shapes.splice(shapes.begin(), squares);
  shapes.splice(shapes.begin(), triangles);

  out << "Vertices: " << verticesCount << '\n' << "Triangles: " << triangleCount << '\n' << "Squares: " << squareCount << '\n'
      << "Rectangles: " << rectangleCount << '\n' << "Points: ";
  for (const auto &point: points)
  {
    out << point << ' ';
  }
  out << '\n' << "Shapes: ";
  for (const auto &shape: shapes)
  {
    out << '\n' << shape;
  }
}

void kosnitskiy::readShapes(std::istream &in, std::list<Shape> &shapes)
{
  shapes.insert(shapes.begin(), std::istream_iterator<Shape>(in), std::istream_iterator<Shape>());
  if (in.fail() && !in.eof())
  {
    throw std::invalid_argument("File contains invalid information");
  }
}

bool kosnitskiy::isRectangle(Shape &shape)
{
  if (shape.size() != 4)
  {
    return false;
  }
  const std::vector<kosnitskiy::Shape::Point> &points = shape.getPoints();
  kosnitskiy::Shape::Point A = points[0];
  kosnitskiy::Shape::Point B{};
  kosnitskiy::Shape::Point C{};
  kosnitskiy::Shape::Point D{};
  bool isBFound = false;
  bool isCFound = false;
  bool isDFound = false;
  for (int i = 1; i < 4; i++)
  {
    if (points[i].x == A.x)
    {
      if (isBFound)
      {
        return false;
      }
      isBFound = true;
      B = points[i];
    }
    else if (points[i].y == A.y)
    {
      if (isDFound)
      {
        return false;
      }
      isDFound = true;
      D = points[i];
    }
    else
    {
      if (isCFound)
      {
        return false;
      }
      isCFound = true;
      C = points[i];
    }
  }

  if (!isBFound || !isCFound || !isDFound)
  {
    return false;
  }

  if (((A.y - D.y) != (B.y - C.y)) || ((A.x - B.x) != (D.x - C.x)))
  {
    return false;
  }

  return true;
}

bool kosnitskiy::isSquare(Shape &shape)
{
  if (isDot(shape))
  {
    return true;
  }
  if (!isRectangle(shape))
  {
    return false;
  }
  const std::vector<kosnitskiy::Shape::Point> &points = shape.getPoints();
  kosnitskiy::Shape::Point A = points[0];
  for (int i = 1; i < 4; i++)
  {
    if (std::abs(A.x - points[i].x) == std::abs(A.y - points[i].y))
    {
      return true;
    }
  }
  return false;
}

bool kosnitskiy::isDot(Shape &shape)
{
  int x = shape.getPoints()[0].x;
  int y = shape.getPoints()[0].y;
  for (int i = 1; i < 4; i++)
  {
    if (x != shape.getPoints()[i].x || y != shape.getPoints()[i].y)
    {
      return false;
    }
  }
  return true;
}

bool kosnitskiy::isLine(Shape &shape)
{
  const std::vector<kosnitskiy::Shape::Point> &points = shape.getPoints();
  kosnitskiy::Shape::Point A = points[0];
  int counter = 0;
  for (int i = 1; i < 4; i++)
  {
    if (A.x == points[i].x && A.y == points[i].y)
    {
      counter++;
    }
  }
  if (counter == 0)
  {
    return false;
  }
  if (counter == 3 || counter == 2)
  {
    return true;
  }
  if (counter == 1)
  {
    kosnitskiy::Shape::Point B{};
    int bI = 0;
    if (A.x == points[1].x && A.y == points[1].y)
    {
      bI = 2;
      B = points[2];
    }
    else
    {
      bI = 1;
      B = points[1];
    }
    bool isFound = false;
    for (int i = 1; i < 4; i++)
    {
      if (i != bI && B.x == points[i].x && B.y == points[i].y)
      {
        isFound = true;
        break;
      }
    }
    if (!isFound)
    {
      return false;
    }
    return true;
  }
  return false;
}
