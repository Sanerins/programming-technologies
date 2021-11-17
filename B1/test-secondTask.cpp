#include <boost/test/unit_test.hpp>
#include <iostream>
#include <fstream>
#include "secondTask.hpp"

using namespace kosnitskiy;

BOOST_AUTO_TEST_SUITE(task2)

  BOOST_AUTO_TEST_CASE (emptyfileReading)
  {
    std::ofstream testFile("textArray.txt", std::ios::trunc);
    testFile.close();

    const char file[] = "textArray.txt";
    std::ifstream fileReader(file);
    std::stringstream out;

    BOOST_CHECK_NO_THROW(secondTask(fileReader, out));
    BOOST_CHECK_EQUAL(out.str(), "");
  }

  BOOST_AUTO_TEST_CASE (fileReading)
  {
    std::ofstream testFile("textArray.txt", std::ios::trunc);
    testFile << "gregmanTestrarboy k;lsdf/ew";
    testFile.close();

    const char file[] = "textArray.txt";
    std::ifstream fileReader(file);
    std::stringstream out;

    BOOST_CHECK_NO_THROW(secondTask(fileReader, out));
    BOOST_CHECK_EQUAL(out.str(), "gregmanTestrarboy k;lsdf/ew");
  }

BOOST_AUTO_TEST_SUITE_END()
