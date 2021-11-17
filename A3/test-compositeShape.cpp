#include <boost/test/unit_test.hpp>

#define _USE_MATH_DEFINES

#include <cmath>
#include <memory>
#include "shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "base-types.hpp"

using namespace kosnitskiy;

BOOST_AUTO_TEST_SUITE(compositeShape)

  BOOST_AUTO_TEST_CASE (addingShapesArea)
  {
    std::shared_ptr<Rectangle> rect1(new Rectangle{{6, 8}, 8, 7});
    std::shared_ptr<Circle> circle1(new Circle{{12, 16}, 3});
    CompositeShape test;

    test.add(rect1);
    BOOST_CHECK_EQUAL(test.getArea(), rect1->getArea());

    test.add(circle1);
    BOOST_CHECK_EQUAL(test.getArea(), (rect1->getArea() + circle1->getArea()));

    CompositeShape empty;
    BOOST_CHECK_EQUAL(empty.getArea(), 0);
  }

  BOOST_AUTO_TEST_CASE (dependance)
  {
    std::shared_ptr<Rectangle> rect1(new Rectangle{{6, 8}, 8, 7});
    double oldArea = rect1->getArea();
    CompositeShape test;

    test.add(rect1);
    rect1->scale(2);
    BOOST_CHECK_EQUAL(test.getArea(), rect1->getArea());
    BOOST_CHECK_EQUAL(test.getArea(), (oldArea * 4));
  }

  BOOST_AUTO_TEST_CASE (scale)
  {
    std::shared_ptr<Rectangle> rect1(new Rectangle{{6, 8}, 8, 7});
    std::shared_ptr<Circle> circle1(new Circle{{12, 16}, 3});
    CompositeShape test;

    test.add(rect1);
    test.add(circle1);
    test.scale(1.5);
    BOOST_CHECK_EQUAL(test.getArea(), (rect1->getArea() + circle1->getArea()));
  }

  BOOST_AUTO_TEST_CASE (move)
  {
    std::shared_ptr<Rectangle> rect1(new Rectangle{{6, 8}, 8, 7});
    std::shared_ptr<Circle> circle1(new Circle{{12, 16}, 3});
    CompositeShape test;

    test.add(rect1);
    test.add(circle1);
    double oldArea = test.getArea();
    test.move({8, -7});
    BOOST_CHECK_EQUAL(test.getArea(), oldArea);
    test.move(6, 8);
    BOOST_CHECK_EQUAL(test.getArea(), oldArea);
  }

  BOOST_AUTO_TEST_CASE (index)
  {
    std::shared_ptr<Rectangle> rect1(new Rectangle{{6, 8}, 8, 7});
    std::shared_ptr<Circle> circle1(new Circle{{12, 16}, 3});
    CompositeShape test;

    test.add(rect1);
    test.add(circle1);
    BOOST_CHECK_EQUAL(rect1->getArea(), test[0]->getArea());
    BOOST_CHECK_EQUAL(circle1->getArea(), test[1]->getArea());
  }

  BOOST_AUTO_TEST_CASE(polymorph)
  {
    Rectangle rect1({7, 5}, 10, 15);
    std::shared_ptr<Shape> shape_ptr = std::make_shared<Rectangle>(rect1);
    std::shared_ptr<Circle> circle_ptr(new Circle{{12, 16}, 3});
    std::shared_ptr<Shape> circle_shape_ptr = std::make_shared<Circle>(*circle_ptr);
    CompositeShape composite;

    composite.add(shape_ptr);
    composite.add(circle_shape_ptr);
    BOOST_CHECK_EQUAL(shape_ptr->getArea(), composite[0]->getArea());
    BOOST_CHECK_EQUAL(circle_shape_ptr->getArea(), composite[1]->getArea());
  }

  BOOST_AUTO_TEST_CASE(constructors)
  {
    std::shared_ptr<Rectangle> rect1(new Rectangle{{6, 8}, 8, 7});
    std::shared_ptr<Circle> circle1(new Circle{{12, 16}, 3});
    CompositeShape test1;

    test1.add(rect1);
    test1.add(circle1);
    CompositeShape test2 = test1;
    BOOST_CHECK_EQUAL(test1.getArea(), test2.getArea());
    CompositeShape test3 = std::move(test1);
    BOOST_CHECK_EQUAL(test2.getArea(), test3.getArea());
  }

  BOOST_AUTO_TEST_CASE(operators)
  {
    std::shared_ptr<Rectangle> rect1(new Rectangle{{6, 8}, 8, 7});
    std::shared_ptr<Circle> circle1(new Circle{{12, 16}, 3});

    CompositeShape test1;
    test1.add(rect1);
    test1.add(circle1);

    CompositeShape test2;
    test2.add(rect1);
    test2 = test1;

    BOOST_CHECK_EQUAL(test1.getArea(), test2.getArea());

    CompositeShape test3;
    test3.add(rect1);
    test3 = std::move(test1);

    BOOST_CHECK_EQUAL(test2.getArea(), test3.getArea());
  }

  BOOST_AUTO_TEST_CASE(getFrameRect)
  {
    CompositeShape test;
    std::shared_ptr<Rectangle> rect1(new Rectangle{{0, 0}, 8, 8});
    std::shared_ptr<Rectangle> rect2(new Rectangle{{10, 10}, 2, 2});
    std::shared_ptr<Circle> circle1(new Circle{{-9, -9}, 10});

    test.add(rect1);
    BOOST_CHECK_EQUAL(test.getFrameRect().width, 8);
    BOOST_CHECK_EQUAL(test.getFrameRect().height, 8);

    BOOST_CHECK_EQUAL(test.getFrameRect().pos.x, 0);
    BOOST_CHECK_EQUAL(test.getFrameRect().pos.y, 0);

    test.add(rect2);
    BOOST_CHECK_EQUAL(test.getFrameRect().width, -(0 - 4) + (10 + 1));
    BOOST_CHECK_EQUAL(test.getFrameRect().height, -(0 - 4) + (10 + 1));

    BOOST_CHECK_EQUAL(test.getFrameRect().pos.x, (-4 + 11) / 2.0);
    BOOST_CHECK_EQUAL(test.getFrameRect().pos.y, (-4 + 11) / 2.0);

    test.add(circle1);
    BOOST_CHECK_EQUAL(test.getFrameRect().width, -(-9 - 10) + (10 + 1));
    BOOST_CHECK_EQUAL(test.getFrameRect().height, -(-9 - 10) + (10 + 1));

    BOOST_CHECK_EQUAL(test.getFrameRect().pos.x, (-19 + 11) / 2.0);
    BOOST_CHECK_EQUAL(test.getFrameRect().pos.y, (-19 + 11) / 2.0);
  }

  BOOST_AUTO_TEST_CASE(swapper)
  {
    std::shared_ptr<Rectangle> rect1(new Rectangle{{0, 0}, 8, 8});
    std::shared_ptr<Circle> circle1(new Circle{{-9, -9}, 10});
    CompositeShape test1;
    test1.add(rect1);

    CompositeShape test2;
    test2.add(circle1);

    std::swap(test1, test2);
    BOOST_CHECK_EQUAL(test1.getArea(), circle1->getArea());
    BOOST_CHECK_EQUAL(test2.getArea(), rect1->getArea());
    std::swap(test1, test1);
    BOOST_CHECK_EQUAL(test1.getArea(), circle1->getArea());
  }

  BOOST_AUTO_TEST_CASE (remove)
  {
    std::shared_ptr<Rectangle> rect1(new Rectangle{{6, 8}, 8, 7});
    std::shared_ptr<Circle> circle1(new Circle{{12, 16}, 3});
    CompositeShape test;
    test.add(rect1);
    BOOST_CHECK_EQUAL(test.getArea(), rect1->getArea());
    test.add(circle1);
    BOOST_CHECK_EQUAL(test.getArea(), (rect1->getArea() + circle1->getArea()));
    test.add(rect1);

    test.remove(0);
    BOOST_CHECK_EQUAL(test.getArea(), circle1->getArea() + rect1->getArea());
    test.remove(1);
    BOOST_CHECK_EQUAL(test.getArea(), circle1->getArea());
    test.remove(0);
    BOOST_CHECK_EQUAL(test.getArea(), 0);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(extendedCompositeTest)
  const CompositeShape testConst;
  CompositeShape test;
  std::shared_ptr<Rectangle> rect_ptr(new Rectangle{{6, 8}, 8, 7});
  std::shared_ptr<Circle> circle_ptr(new Circle{{12, 16}, 3});
  std::shared_ptr<Shape> shape_ptr = std::make_shared<Rectangle>(*rect_ptr);
  const std::shared_ptr<Rectangle> rect_ptr_const(new Rectangle{{6, 8}, 8, 7});
  const std::shared_ptr<Circle> circle_ptr_const(new Circle{{12, 16}, 3});
  const std::shared_ptr<Shape> shape_ptr_const = std::make_shared<Rectangle>(*rect_ptr);

  std::shared_ptr<Shape> empty_ptr;
  const std::shared_ptr<Shape> empty_ptr_const;

  BOOST_AUTO_TEST_CASE(emptyConstructor)
  {
    BOOST_CHECK_NO_THROW(CompositeShape tester);
    BOOST_CHECK_NO_THROW(const CompositeShape tester);
  }

  BOOST_AUTO_TEST_CASE(add)
  {
    for (int i = 0; i < 3; i++)
    {
      BOOST_CHECK_NO_THROW(test.add(rect_ptr));
      BOOST_CHECK_NO_THROW(test.add(circle_ptr));
      BOOST_CHECK_NO_THROW(test.add(shape_ptr));
      BOOST_CHECK_NO_THROW(test.add(rect_ptr_const));
      BOOST_CHECK_NO_THROW(test.add(circle_ptr_const));
      BOOST_CHECK_NO_THROW(test.add(shape_ptr_const));
      BOOST_CHECK_THROW(test.add(empty_ptr), std::invalid_argument);
      BOOST_CHECK_THROW(test.add(empty_ptr_const), std::invalid_argument);
    }
  }

  BOOST_AUTO_TEST_CASE(elementChanging)
  {
    for (int i = 0; i < 18; i++)
    {
      double area = 0;
      rectangle_t frameRect;

      BOOST_CHECK_NO_THROW(area = test[i]->getArea());
      BOOST_CHECK_NO_THROW(frameRect = test[i]->getFrameRect());

      BOOST_CHECK_NO_THROW(test[i]->scale(2));

      BOOST_CHECK_EQUAL(area * 4, test[i]->getArea());
      BOOST_CHECK_EQUAL(frameRect.height * 2, test[i]->getFrameRect().height);
      BOOST_CHECK_EQUAL(frameRect.width * 2, test[i]->getFrameRect().width);
      BOOST_CHECK_EQUAL(frameRect.pos.x, test[i]->getFrameRect().pos.x);
      BOOST_CHECK_EQUAL(frameRect.pos.y, test[i]->getFrameRect().pos.y);

      double x = 0;
      double y = 0;

      BOOST_CHECK_NO_THROW(x = test[i]->getFrameRect().pos.x);
      BOOST_CHECK_NO_THROW(y = test[i]->getFrameRect().pos.y);

      BOOST_CHECK_NO_THROW(test[i]->move(6, 8));
      BOOST_CHECK_EQUAL(x + 6, test[i]->getFrameRect().pos.x);
      BOOST_CHECK_EQUAL(y + 8, test[i]->getFrameRect().pos.y);
    }
  }

  BOOST_AUTO_TEST_CASE(copyConstructor)
  {
    BOOST_CHECK_NO_THROW(const CompositeShape testerConst(test));
    const CompositeShape testerConst(test);

    BOOST_CHECK_EQUAL(testerConst.getArea(), test.getArea());
    for (int i = 0; i < 18; i++)
    {
      BOOST_CHECK_EQUAL(testerConst[i]->getArea(), test[i]->getArea());
    }

    BOOST_CHECK_NO_THROW(testerConst.getFrameRect());

    BOOST_CHECK_NO_THROW(const CompositeShape tester(test));
    CompositeShape tester(test);

    BOOST_CHECK_EQUAL(tester.getArea(), test.getArea());
    for (int i = 0; i < 18; i++)
    {
      BOOST_CHECK_EQUAL(tester[i]->getArea(), test[i]->getArea());
    }

    BOOST_CHECK_NO_THROW(tester.getFrameRect());

    CompositeShape nullShape1;
    BOOST_CHECK_NO_THROW(CompositeShape nullShape2(nullShape1));
  }

  BOOST_AUTO_TEST_CASE(copyOperator)
  {
    CompositeShape tester;
    BOOST_CHECK_NO_THROW(tester = test);

    BOOST_CHECK_EQUAL(tester.getArea(), test.getArea());
    for (int i = 0; i < 18; i++)
    {
      BOOST_CHECK_EQUAL(tester[i]->getArea(), test[i]->getArea());
    }

    BOOST_CHECK_NO_THROW(tester.getFrameRect());

    CompositeShape nullTest;
    BOOST_CHECK_NO_THROW(tester = nullTest);
  }

  BOOST_AUTO_TEST_CASE(remove)
  {
    double area = 0;
    double newArea = 0;

    for (int i = 0; i < 18; i++)
    {
      area = round((test.getArea() - test[0]->getArea()) * 1000) / 1000;
      BOOST_CHECK_NO_THROW(test.remove(0));
      newArea = round((test.getArea()) * 1000) / 1000;
      BOOST_CHECK_EQUAL(newArea, area);
      if (i != 17)
      {
        BOOST_CHECK_NO_THROW(test.getFrameRect());
      }
    }
  }

  BOOST_AUTO_TEST_CASE(emptyShape)
  {
    for (int i = -2; i <= 2; i++)
    {
      BOOST_CHECK_THROW(test[i], std::invalid_argument);
      BOOST_CHECK_THROW(test.remove(i), std::invalid_argument);

      BOOST_CHECK_THROW(testConst[i], std::invalid_argument);
    }

    BOOST_CHECK_EQUAL(test.getArea(), 0);
    BOOST_CHECK_EQUAL(testConst.getArea(), 0);

    BOOST_CHECK_THROW(testConst.getFrameRect(), kosnitskiy::empty_shape);
    BOOST_CHECK_THROW(testConst.getFrameRect(), kosnitskiy::empty_shape);

    BOOST_CHECK_NO_THROW(test.move(5, 6));
    BOOST_CHECK_NO_THROW(test.move({5, 6}));
    BOOST_CHECK_NO_THROW(test.scale(8));
  }

BOOST_AUTO_TEST_SUITE_END()
