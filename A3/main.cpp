#include <iostream>
#include <memory>
#include "base-types.hpp"
#include "shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace kosnitskiy;

void printInfo(const Shape &src);

void moveCenterToPoint(Shape &src, const point_t &point);

void changeCenterByAxis(Shape &src, int x, int y);

void scaleShape(Shape &src, double parameter);

int main()
{
  Rectangle rect1({7, 5}, 10, 15);
  Rectangle rect2({9, 3}, 24, 12);
  Circle circle1({8, 9}, 10);
  Circle circle2({5, 5}, 7);
  Shape &shapeRec = rect1;
  Shape &shapeCirc = circle1;

  printInfo(rect1);
  printInfo(rect2);
  printInfo(circle1);
  printInfo(circle2);
  printInfo(shapeRec);
  printInfo(shapeCirc);

  moveCenterToPoint(rect1, {12, 17});
  moveCenterToPoint(rect2, {6, 7});
  moveCenterToPoint(circle1, {12, 34});
  moveCenterToPoint(circle2, {9, 10});
  moveCenterToPoint(shapeRec, {1, -5});
  moveCenterToPoint(shapeCirc, {-3, 4});

  changeCenterByAxis(rect1, 4, 8);
  changeCenterByAxis(rect2, -3, 6);
  changeCenterByAxis(circle1, 2, -1);
  changeCenterByAxis(circle2, 8, 10);
  changeCenterByAxis(shapeRec, -5, -7);
  changeCenterByAxis(shapeCirc, -1, 3);

  scaleShape(rect1, 1.5);
  scaleShape(rect2, 2);
  scaleShape(circle1, 3);
  scaleShape(circle2, 2.5);
  scaleShape(shapeRec, 0.5);
  scaleShape(shapeCirc, 0.1);

  std::cout << "\n\n ---COMPOSITE TEST--- \n\n";

  std::shared_ptr<Rectangle> rect_ptr(new Rectangle{{6, 8}, 8, 7});
  std::shared_ptr<Circle> circle_ptr(new Circle{{12, 16}, 3});
  std::shared_ptr<Shape> shape_ptr = std::make_shared<Rectangle>(*rect_ptr);
  CompositeShape composite;
  composite.add(rect_ptr);
  printInfo(composite);
  composite.add(circle_ptr);
  printInfo(composite);
  composite.add(shape_ptr);
  printInfo(composite);
  moveCenterToPoint(composite, {6, 9});
  changeCenterByAxis(composite, -4, 20);
  scaleShape(composite, 0.5);
}

void printInfo(const Shape &src)
{
  rectangle_t shapeFrame = src.getFrameRect();

  std::cout << "\nArea of the provided shape: " << src.getArea() << "\nShape frame width: " << shapeFrame.width << " height: "
            << shapeFrame.height << " center: " << shapeFrame.pos.x << " and " << shapeFrame.pos.y << "\n";
}

void moveCenterToPoint(Shape &src, const point_t &point)
{
  std::cout << "\nThe measurements of 'point_t' used for shifting Shape: " << point.x << " and " << point.y << "\n";
  rectangle_t shapeFrame = src.getFrameRect();
  std::cout << "Center of shape before point move: " << shapeFrame.pos.x << " and " << shapeFrame.pos.y << "\n";
  src.move(point);
  shapeFrame = src.getFrameRect();
  std::cout << "Center of shape after point move: " << shapeFrame.pos.x << " and " << shapeFrame.pos.y << "\n\n";
}

void changeCenterByAxis(Shape &src, int x, int y)
{
  std::cout << "\nThe axis values used for movement: " << x << " and " << y << "\n";
  rectangle_t shapeFrame = src.getFrameRect();
  std::cout << "Center of shape before axis move: " << shapeFrame.pos.x << " and " << shapeFrame.pos.y << "\n";
  src.move(x, y);
  shapeFrame = src.getFrameRect();
  std::cout << "Center of shape after axis move: " << shapeFrame.pos.x << " and " << shapeFrame.pos.y << "\n\n";
}

void scaleShape(Shape &src, double parameter)
{
  std::cout << "\nThe shape before " << parameter << " scale: ";
  printInfo(src);
  src.scale(parameter);
  std::cout << "\nThe shape after " << parameter << " scale: ";
  printInfo(src);
}
