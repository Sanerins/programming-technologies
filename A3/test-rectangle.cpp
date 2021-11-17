#include <boost/test/unit_test.hpp>

#include "rectangle.hpp"
#include "base-types.hpp"

using namespace kosnitskiy;

BOOST_AUTO_TEST_SUITE(rectangle)

  BOOST_AUTO_TEST_CASE (area)
  {
    double x = 10;
    double y = 8;
    Rectangle rect1({7, 5}, x, y);

    BOOST_CHECK_EQUAL(rect1.getArea(), x * y);
  }

  BOOST_AUTO_TEST_CASE (frame)
  {
    double x = 10;
    double y = 8;
    Rectangle rect1({7, 5}, x, y);

    BOOST_CHECK_EQUAL(rect1.getFrameRect().height, y);
    BOOST_CHECK_EQUAL(rect1.getFrameRect().width, x);
    BOOST_CHECK_EQUAL(rect1.getFrameRect().pos.x, 7);
    BOOST_CHECK_EQUAL(rect1.getFrameRect().pos.y, 5);
  }

  BOOST_AUTO_TEST_CASE (move)
  {
    Rectangle rect1({7, 5}, 10, 15);
    double oldArea = rect1.getArea();
    point_t newPos = {8, -7};

    rect1.move(newPos);
    BOOST_CHECK_EQUAL(rect1.getFrameRect().pos.x, newPos.x);
    BOOST_CHECK_EQUAL(rect1.getFrameRect().pos.y, newPos.y);
    BOOST_CHECK_EQUAL(rect1.getArea(), oldArea);

    rect1.move(6, 8);
    BOOST_CHECK_EQUAL(rect1.getFrameRect().pos.x, newPos.x + 6);
    BOOST_CHECK_EQUAL(rect1.getFrameRect().pos.y, newPos.y + 8);
    BOOST_CHECK_EQUAL(rect1.getArea(), oldArea);
  }

  BOOST_AUTO_TEST_CASE (scale)
  {
    Rectangle rect1({7, 5}, 10, 15);
    double param = 4.5;
    double oldArea = rect1.getArea();

    rect1.scale(param);
    BOOST_CHECK_EQUAL(rect1.getArea(), oldArea * param * param);
  }

BOOST_AUTO_TEST_SUITE_END()
