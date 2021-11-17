#include <boost/test/unit_test.hpp>

#include <memory>
#include <cmath>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "base-types.hpp"

using namespace kosnitskiy;

BOOST_AUTO_TEST_SUITE(exceptions)

  BOOST_AUTO_TEST_CASE(constructorExceptions)
  {
    BOOST_CHECK_THROW(Rectangle wrongRect({7, 7}, -10, 6), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle wrongRect({7, 7}, -10, -6), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle wrongRect({7, 7}, 10, -6), std::invalid_argument);
    BOOST_CHECK_THROW(Circle wrongCircle({7, 7}, -10), std::invalid_argument);

    CompositeShape test;
    BOOST_CHECK_THROW(test.getFrameRect(), kosnitskiy::empty_shape);
    BOOST_CHECK_THROW(test[-2], std::invalid_argument);
    BOOST_CHECK_THROW(test[6], std::invalid_argument);
    BOOST_CHECK_THROW(test[0], std::invalid_argument);
    BOOST_CHECK_THROW(test.remove(7), std::invalid_argument);
    BOOST_CHECK_THROW(test.remove(-1), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(scalingExceptions)
  {
    std::shared_ptr<Rectangle> rect1(new Rectangle{{6, 8}, 8, 7});
    std::shared_ptr<Circle> circle1(new Circle{{12, 16}, 3});
    CompositeShape shape1;

    shape1.add(rect1);
    shape1.add(circle1);
    BOOST_CHECK_THROW(rect1->scale(-3), std::invalid_argument);
    BOOST_CHECK_THROW(circle1->scale(0), std::invalid_argument);
    BOOST_CHECK_THROW(shape1.scale(-0.1), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
