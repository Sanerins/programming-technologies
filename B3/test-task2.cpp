#include <boost/test/unit_test.hpp>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "factorial-container.hpp"

using namespace kosnitskiy;

BOOST_AUTO_TEST_SUITE(task2)

  std::stringstream out;

  BOOST_AUTO_TEST_CASE (iterators)
  {
    Factorials factorials;
    std::copy(factorials.cbegin(), factorials.cend(), std::ostream_iterator<Factorials::value_type>(out, " "));
    out << '\n';
    std::copy(factorials.crbegin(), factorials.crend(), std::ostream_iterator<Factorials::value_type>(out, " "));
    out << '\n';
    BOOST_CHECK_EQUAL(out.str(), "1 2 6 24 120 720 5040 40320 362880 3628800 \n3628800 362880 40320 5040 720 120 24 6 2 1 \n");
  }

  BOOST_AUTO_TEST_CASE (defaultIter)
  {
    Factorials::iterator iter;
    Factorials factorials;
    BOOST_CHECK(iter == factorials.end());
  }

  BOOST_AUTO_TEST_CASE (increment)
  {
    Factorials factorials;
    Factorials::iterator iter = factorials.begin();
    BOOST_CHECK(*iter == 1);
    iter++;
    iter++;
    BOOST_CHECK(*iter == 6);
  }

  BOOST_AUTO_TEST_CASE (decrement)
  {
    Factorials factorials;
    Factorials::iterator iter = factorials.end();
    iter--;
    BOOST_CHECK(*iter == 3628800);
    iter--;
    BOOST_CHECK(*iter == 362880);
  }

BOOST_AUTO_TEST_SUITE_END()
