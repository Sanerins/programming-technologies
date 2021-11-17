#include <boost/test/unit_test.hpp>
#include <iostream>
#include "sortingDirection.hpp"
#include "firstTask.hpp"

using namespace kosnitskiy;

BOOST_AUTO_TEST_SUITE(task1)
  SortingDirection up = ASCENDING;
  SortingDirection down = DESCENDING;

  BOOST_AUTO_TEST_CASE (testExept)
  {
    std::stringstream errIn("5 3 6 7 0 gag 4 6 3 ");

    BOOST_CHECK_THROW(firstTask(up, errIn), std::runtime_error);
  }

  BOOST_AUTO_TEST_CASE (nullInput)
  {
    std::stringstream in("");
    std::stringstream out;

    BOOST_CHECK_NO_THROW(firstTask(up, in, out));
    BOOST_CHECK_EQUAL(out.str(), "\n\n\n");
  }

  BOOST_AUTO_TEST_CASE (upSort)
  {
    std::stringstream in("3 5 1 2 9 3 ");
    std::stringstream out;

    BOOST_CHECK_NO_THROW(firstTask(up, in, out));
    BOOST_CHECK_EQUAL(out.str(), "1 2 3 3 5 9 \n1 2 3 3 5 9 \n1 2 3 3 5 9 \n");
  }

  BOOST_AUTO_TEST_CASE (downSort)
  {
    std::stringstream in("3 5 1 2 9 3 ");
    std::stringstream out;

    BOOST_CHECK_NO_THROW(firstTask(down, in, out));
    BOOST_CHECK_EQUAL(out.str(), "9 5 3 3 2 1 \n9 5 3 3 2 1 \n9 5 3 3 2 1 \n");
  }

BOOST_AUTO_TEST_SUITE_END()
