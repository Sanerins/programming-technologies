#include <boost/test/unit_test.hpp>

#define _USE_MATH_DEFINES

#include <cmath>
#include <memory>
#include "base-types.hpp"
#include "shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace kosnitskiy;

BOOST_AUTO_TEST_SUITE(ShapesInShapes)

  std::shared_ptr<Rectangle> rect_ptr(new Rectangle{{6, 8}, 8, 7});
  std::shared_ptr<Circle> circle_ptr(new Circle{{12, 16}, 3});
  std::shared_ptr<Shape> shape_ptr = std::make_shared<Rectangle>(*rect_ptr);
  const std::shared_ptr<Rectangle> rect_ptr_const(new Rectangle{{6, 8}, 8, 7});
  const std::shared_ptr<Circle> circle_ptr_const(new Circle{{12, 16}, 3});
  const std::shared_ptr<Shape> shape_ptr_const = std::make_shared<Rectangle>(*rect_ptr);

  CompositeShape test;

  BOOST_AUTO_TEST_CASE(shapeOfShapes)
  {
    std::shared_ptr<CompositeShape> tester(new CompositeShape);
    const std::shared_ptr<CompositeShape> testerConst(new CompositeShape);

    BOOST_CHECK_NO_THROW(tester->add(rect_ptr));
    BOOST_CHECK_NO_THROW(tester->add(circle_ptr));
    BOOST_CHECK_NO_THROW(tester->add(shape_ptr));
    BOOST_CHECK_NO_THROW(tester->add(rect_ptr_const));
    BOOST_CHECK_NO_THROW(tester->add(circle_ptr_const));
    BOOST_CHECK_NO_THROW(tester->add(shape_ptr_const));

    std::shared_ptr<CompositeShape> tester2(new CompositeShape);
    BOOST_CHECK_NO_THROW(tester2 = tester);
    std::shared_ptr<CompositeShape> tester3(new CompositeShape(*tester2));

    test.add(tester);
    test.add(testerConst);
    test.add(tester2);
    test.add(tester3);
  }

  BOOST_AUTO_TEST_CASE(copyConstructor)
  {
    BOOST_CHECK_NO_THROW(const CompositeShape testerConst(test));
    const CompositeShape testerConst(test);

    BOOST_CHECK_EQUAL(testerConst.getArea(), test.getArea());
    for (int i = 0; i < 4; i++)
    {
      BOOST_CHECK_EQUAL(testerConst[i]->getArea(), test[i]->getArea());
    }
    BOOST_CHECK_NO_THROW(testerConst.getFrameRect());

    BOOST_CHECK_NO_THROW(CompositeShape tester(test));
    CompositeShape tester(test);

    BOOST_CHECK_EQUAL(tester.getArea(), test.getArea());
    for (int i = 0; i < 4; i++)
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
    for (int i = 0; i < 4; i++)
    {
      BOOST_CHECK_EQUAL(tester[i]->getArea(), test[i]->getArea());
    }

    BOOST_CHECK_NO_THROW(tester.getFrameRect());

    CompositeShape nullTest;
    BOOST_CHECK_NO_THROW(tester = nullTest);
  }

  BOOST_AUTO_TEST_CASE(moveConstructor)
  {
    CompositeShape testerM(test);
    const CompositeShape movedTesterConst(std::move(testerM));

    BOOST_CHECK_EQUAL(movedTesterConst.getArea(), test.getArea());
    for (int i = 0; i < 4; i++)
    {
      BOOST_CHECK_EQUAL(movedTesterConst[i]->getArea(), test[i]->getArea());
    }

    BOOST_CHECK_NO_THROW(movedTesterConst.getFrameRect());

    CompositeShape tester(test);
    CompositeShape movedTester(std::move(tester));

    BOOST_CHECK_EQUAL(movedTester.getArea(), test.getArea());
    for (int i = 0; i < 4; i++)
    {
      BOOST_CHECK_EQUAL(movedTester[i]->getArea(), test[i]->getArea());
    }

    BOOST_CHECK_NO_THROW(movedTester.getFrameRect());

    CompositeShape nullShape1;
    BOOST_CHECK_NO_THROW(CompositeShape nullShape2(std::move(nullShape1)));
  }

  BOOST_AUTO_TEST_CASE(moveOperator)
  {
    CompositeShape tester;
    CompositeShape movedTester;
    tester = test;
    BOOST_CHECK_NO_THROW(movedTester = std::move(tester));

    BOOST_CHECK_EQUAL(movedTester.getArea(), test.getArea());
    for (int i = 0; i < 4; i++)
    {
      BOOST_CHECK_EQUAL(movedTester[i]->getArea(), test[i]->getArea());
    }
    BOOST_CHECK_NO_THROW(movedTester.getFrameRect());

    CompositeShape nullTest;
    BOOST_CHECK_NO_THROW(movedTester = nullTest);
  }

  BOOST_AUTO_TEST_CASE(remove)
  {
    double area = 0;
    double newArea = 0;

    for (int i = 0; i < 4; i++)
    {
      area = round((test.getArea() - test[0]->getArea()) * 1000) / 1000;
      BOOST_CHECK_NO_THROW(test.remove(0));
      newArea = round((test.getArea()) * 1000) / 1000;
      BOOST_CHECK_EQUAL(newArea, area);
    }
  }

  BOOST_AUTO_TEST_CASE(checkingGetFrameRectangle)
  {
    std::shared_ptr<Rectangle> rect(new Rectangle{{6, 8}, 8, 7});
    std::shared_ptr<CompositeShape> shallow1(new CompositeShape);
    std::shared_ptr<CompositeShape> shallow2(new CompositeShape);
    std::shared_ptr<CompositeShape> shallow3(new CompositeShape);
    std::shared_ptr<CompositeShape> filled1(new CompositeShape);

    filled1->add(rect);
    CompositeShape swapTest = *shallow1;
    double oldArea = rect->getArea();
    double oldX = rect->getFrameRect().pos.x;

    BOOST_CHECK_THROW(shallow1->add(shallow1), std::invalid_argument);
    BOOST_CHECK_THROW(test.getFrameRect(), kosnitskiy::empty_shape);
    BOOST_CHECK_EQUAL(test.getArea(), 0);
    BOOST_CHECK_NO_THROW(test.move(5, 5));
    BOOST_CHECK_NO_THROW(test.scale(2));
    BOOST_CHECK_EQUAL(test.getSize(), 0);
    BOOST_CHECK_NO_THROW(test.scale(2));
    BOOST_CHECK_NO_THROW(std::swap(test, swapTest));
    BOOST_CHECK_NO_THROW(std::swap(test, swapTest));

    test.add(shallow1);
    BOOST_CHECK_THROW(test.getFrameRect(), kosnitskiy::empty_shape);
    BOOST_CHECK_EQUAL(test.getArea(), 0);
    BOOST_CHECK_NO_THROW(test.move(5, 5));
    BOOST_CHECK_NO_THROW(test.scale(2));
    BOOST_CHECK_EQUAL(test.getSize(), 1);
    BOOST_CHECK_NO_THROW(std::swap(test, swapTest));
    BOOST_CHECK_NO_THROW(std::swap(test, swapTest));

    test.add(filled1);
    BOOST_CHECK_NO_THROW(test.getFrameRect());
    BOOST_CHECK_EQUAL(test.getArea(), rect->getArea());
    BOOST_CHECK_NO_THROW(test.move(5, 5));
    BOOST_CHECK_EQUAL(test.getFrameRect().pos.x, (oldX + 5));
    BOOST_CHECK_NO_THROW(test.scale(2));
    BOOST_CHECK_EQUAL(test.getArea(), oldArea * 4);
    BOOST_CHECK_EQUAL(test.getSize(), 2);
    BOOST_CHECK_NO_THROW(std::swap(test, swapTest));
    BOOST_CHECK_NO_THROW(std::swap(test, swapTest));
    oldX += 5;
    oldArea *= 4;

    test.remove(1);
    BOOST_CHECK_THROW(test.getFrameRect(), kosnitskiy::empty_shape);
    BOOST_CHECK_EQUAL(test.getArea(), 0);
    BOOST_CHECK_NO_THROW(test.move(5, 5));
    BOOST_CHECK_NO_THROW(test.scale(2));
    BOOST_CHECK_EQUAL(test.getSize(), 1);
    BOOST_CHECK_NO_THROW(std::swap(test, swapTest));
    BOOST_CHECK_NO_THROW(std::swap(test, swapTest));

    test.add(shallow2);
    BOOST_CHECK_THROW(test.getFrameRect(), kosnitskiy::empty_shape);
    BOOST_CHECK_EQUAL(test.getArea(), 0);
    BOOST_CHECK_NO_THROW(test.move(5, 5));
    BOOST_CHECK_NO_THROW(test.scale(2));
    BOOST_CHECK_EQUAL(test.getSize(), 2);
    BOOST_CHECK_NO_THROW(std::swap(test, swapTest));
    BOOST_CHECK_NO_THROW(std::swap(test, swapTest));

    test.add(shallow3);
    BOOST_CHECK_THROW(test.getFrameRect(), kosnitskiy::empty_shape);
    BOOST_CHECK_EQUAL(test.getArea(), 0);
    BOOST_CHECK_NO_THROW(test.move(5, 5));
    BOOST_CHECK_NO_THROW(test.scale(2));
    BOOST_CHECK_EQUAL(test.getSize(), 3);
    BOOST_CHECK_NO_THROW(std::swap(test, swapTest));
    BOOST_CHECK_NO_THROW(std::swap(test, swapTest));

    test.add(filled1);
    BOOST_CHECK_NO_THROW(test.getFrameRect());
    BOOST_CHECK_EQUAL(test.getArea(), rect->getArea());
    BOOST_CHECK_NO_THROW(test.move(5, 5));
    BOOST_CHECK_EQUAL(test.getFrameRect().pos.x, (oldX + 5));
    BOOST_CHECK_NO_THROW(test.scale(2));
    BOOST_CHECK_EQUAL(test.getArea(), oldArea * 4);
    BOOST_CHECK_EQUAL(test.getSize(), 4);
    BOOST_CHECK_NO_THROW(std::swap(test, swapTest));
    BOOST_CHECK_NO_THROW(std::swap(test, swapTest));
    oldX += 5;
    oldArea *= 4;

    test.remove(0);
    BOOST_CHECK_NO_THROW(test.getFrameRect());
    BOOST_CHECK_EQUAL(test.getArea(), rect->getArea());
    BOOST_CHECK_NO_THROW(test.move(5, 5));
    BOOST_CHECK_EQUAL(test.getFrameRect().pos.x, (oldX + 5));
    BOOST_CHECK_NO_THROW(test.scale(2));
    BOOST_CHECK_EQUAL(test.getArea(), oldArea * 4);
    BOOST_CHECK_EQUAL(test.getSize(), 3);
    oldX += 5;
    oldArea *= 4;

    test.remove(0);
    BOOST_CHECK_NO_THROW(test.getFrameRect());
    BOOST_CHECK_EQUAL(test.getArea(), rect->getArea());
    BOOST_CHECK_NO_THROW(test.move(5, 5));
    BOOST_CHECK_EQUAL(test.getFrameRect().pos.x, (oldX + 5));
    BOOST_CHECK_NO_THROW(test.scale(2));
    BOOST_CHECK_EQUAL(test.getArea(), oldArea * 4);
    BOOST_CHECK_EQUAL(test.getSize(), 2);
    oldX += 5;
    oldArea *= 4;

    test.remove(0);
    BOOST_CHECK_NO_THROW(test.getFrameRect());
    BOOST_CHECK_EQUAL(test.getArea(), rect->getArea());
    BOOST_CHECK_NO_THROW(test.move(5, 5));
    BOOST_CHECK_EQUAL(test.getFrameRect().pos.x, (oldX + 5));
    BOOST_CHECK_NO_THROW(test.scale(2));
    BOOST_CHECK_EQUAL(test.getArea(), oldArea * 4);
    BOOST_CHECK_EQUAL(test.getSize(), 1);
    oldX += 5;
    oldArea *= 4;

    test.remove(0);
    BOOST_CHECK_THROW(test.getFrameRect(), kosnitskiy::empty_shape);
    BOOST_CHECK_EQUAL(test.getArea(), 0);
    BOOST_CHECK_NO_THROW(test.move(5, 5));
    BOOST_CHECK_NO_THROW(test.scale(2));
    BOOST_CHECK_EQUAL(test.getSize(), 0);
  }

  BOOST_AUTO_TEST_CASE(miscelanious)
  {
    test.add(rect_ptr);
    test.add(circle_ptr);
    test[0].reset();
    BOOST_CHECK_NO_THROW(test.getArea());
  }

BOOST_AUTO_TEST_SUITE_END();
