#include <boost/test/unit_test.hpp>
#include <iostream>
#include "thirdTask.hpp"

using namespace kosnitskiy;

BOOST_AUTO_TEST_SUITE(task3)

  BOOST_AUTO_TEST_CASE (testExept)
  {
    std::stringstream errIn("5 3 6 7 gag 4 6 3 ");

    BOOST_CHECK_THROW(thirdTask(errIn), std::runtime_error);
  }

  BOOST_AUTO_TEST_CASE (nullInput)
  {
    std::stringstream in("");
    std::stringstream out;

    BOOST_CHECK_NO_THROW(thirdTask(in, out));
    BOOST_CHECK_EQUAL(out.str(), "");
  }

  BOOST_AUTO_TEST_CASE (noZero)
  {
    std::stringstream in("43 576 23 6 32 5 ");
    std::stringstream out;

    BOOST_CHECK_THROW(thirdTask(in, out), std::logic_error);
  }

  BOOST_AUTO_TEST_CASE (taskOne)
  {
    std::stringstream in("3 6 9 4 8 6 10 1 0 ");
    std::stringstream out;

    BOOST_CHECK_NO_THROW(thirdTask(in, out));
    BOOST_CHECK_EQUAL(out.str(), "3 9 1 ");
  }

  BOOST_AUTO_TEST_CASE (taskTwo)
  {
    std::stringstream in("3 6 9 4 8 6 10 2 0 ");
    std::stringstream out;

    BOOST_CHECK_NO_THROW(thirdTask(in, out));
    BOOST_CHECK_EQUAL(out.str(), "3 1 1 1 6 1 1 1 9 1 1 1 4 8 6 1 1 1 10 2 ");
  }

BOOST_AUTO_TEST_SUITE_END()
