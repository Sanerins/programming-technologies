#include <boost/test/unit_test.hpp>

#define _USE_MATH_DEFINES

#include <cmath>
#include "circle.hpp"
#include "base-types.hpp"

using namespace kosnitskiy;

BOOST_AUTO_TEST_SUITE(circle)

  BOOST_AUTO_TEST_CASE (area)
  {
    double x = 10;
    Circle circle1({7, 5}, x);

    BOOST_CHECK_EQUAL(circle1.getArea(), M_PI * x * x);
  }

  BOOST_AUTO_TEST_CASE (frame)
  {
    double x = 10;
    Circle circle1({7, 5}, x);

    BOOST_CHECK_EQUAL(circle1.getFrameRect().height, 2 * x);
    BOOST_CHECK_EQUAL(circle1.getFrameRect().width, 2 * x);
    BOOST_CHECK_EQUAL(circle1.getFrameRect().pos.x, 7);
    BOOST_CHECK_EQUAL(circle1.getFrameRect().pos.y, 5);
  }

  BOOST_AUTO_TEST_CASE (move)
  {
    Circle circle1({7, 5}, 10);
    double oldArea = circle1.getArea();
    point_t newPos = {8, -7};

    circle1.move(newPos);
    BOOST_CHECK_EQUAL(circle1.getFrameRect().pos.x, newPos.x);
    BOOST_CHECK_EQUAL(circle1.getFrameRect().pos.y, newPos.y);
    BOOST_CHECK_EQUAL(circle1.getArea(), oldArea);

    circle1.move(6, 8);
    BOOST_CHECK_EQUAL(circle1.getFrameRect().pos.x, newPos.x + 6);
    BOOST_CHECK_EQUAL(circle1.getFrameRect().pos.y, newPos.y + 8);
    BOOST_CHECK_EQUAL(circle1.getArea(), oldArea);
  }

  BOOST_AUTO_TEST_CASE (scale)
  {
    Circle circle1({7, 5}, 10);
    double param = 4.5;
    double oldArea = circle1.getArea();

    circle1.scale(param);
    BOOST_CHECK_EQUAL(circle1.getArea(), oldArea * param * param);
  }

BOOST_AUTO_TEST_SUITE_END()
