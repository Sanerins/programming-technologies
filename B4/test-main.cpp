#define BOOST_TEST_MODULE "C++ Unit Tests for B3 lab"

#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <exception>
#include "algorithm.hpp"

using namespace kosnitskiy;

BOOST_AUTO_TEST_SUITE(task1)

  BOOST_AUTO_TEST_CASE (workcheck)
  {
    std::vector<DataStruct> vector;
    std::stringstream in;
    std::stringstream out;
    in << "5,4,fld\n"
          "3,-2,man\n"
          "5,5,lol\n"
          "3,-2,manly\n"
          "5,5,lola\n";
    execute(vector, in, out);
    BOOST_CHECK_EQUAL(out.str(), "3,-2,man\n3,-2,manly\n5,4,fld\n5,5,lol\n5,5,lola\n");
  }

  BOOST_AUTO_TEST_CASE (workcheckWithSpaces)
  {
    std::vector<DataStruct> vector;
    std::stringstream in;
    std::stringstream out;
    in << "5,  4 ,  fld\n\n"
          "   3,  -2,    man\n\n"
          "5  ,5 ,lol     \n"
          "3,   -2,manly\n\n\n\n\n"
          "5,5,   lola\n";
    execute(vector, in, out);
    BOOST_CHECK_EQUAL(out.str(), "3,-2,man\n3,-2,manly\n5,4,fld\n5,5,lola\n5,5,lol     \n");
  }

  BOOST_AUTO_TEST_CASE (twoInputsInOneLine)
  {
    std::vector<DataStruct> vector;
    std::stringstream in;
    std::stringstream out;
    in << "5,4,fld 3,-2,man";
    execute(vector, in, out);
    BOOST_CHECK_EQUAL(out.str(), "5,4,fld 3,-2,man\n");
  }

  BOOST_AUTO_TEST_CASE (notEnoughInputStr)
  {
    std::vector<DataStruct> vector;
    std::stringstream in;
    std::stringstream out;
    in << "5,4,";
    BOOST_CHECK_THROW(kosnitskiy::execute(vector, in, out), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE (notEnoughInputArg)
  {
    std::vector<DataStruct> vector;
    std::stringstream in;
    std::stringstream out;
    in << ",4,str";
    BOOST_CHECK_THROW(kosnitskiy::execute(vector, in, out), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE (noProperDelim)
  {
    std::vector<DataStruct> vector;
    std::stringstream in;
    std::stringstream out;
    in << "5 4 str";
    BOOST_CHECK_THROW(kosnitskiy::execute(vector, in, out), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
