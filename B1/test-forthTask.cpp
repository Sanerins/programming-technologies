#include <boost/test/unit_test.hpp>
#include <iostream>
#include <vector>
#include "forthTask.hpp"

using namespace kosnitskiy;

BOOST_AUTO_TEST_SUITE(task4)

  BOOST_AUTO_TEST_CASE (randomness)
  {
    srand(time(nullptr));
  }

  BOOST_AUTO_TEST_CASE (taskDescending)
  {
    for (int i = 0; i < 1; i++)
    {
      std::stringstream out;
      BOOST_CHECK_NO_THROW(forthTask(DESCENDING, 25, out));
      double number;
      std::vector<double> numbers;
      for (int j = 0; j < 25; j++)
      {
        out >> number;
        numbers.push_back(number);
      }

      std::vector<double> sortedNumbers;
      for (int j = 0; j < 25; j++)
      {
        out >> number;
        sortedNumbers.push_back(number);
      }
      std::sort(numbers.begin(), numbers.end(), std::greater<>());
      for (unsigned long j = 0; j < sortedNumbers.size(); j++)
      {
        BOOST_CHECK_EQUAL(sortedNumbers[j], numbers[j]);
      }
    }
  }

  BOOST_AUTO_TEST_CASE (taskAscending)
  {
    for (int i = 0; i < 10; i++)
    {
      std::stringstream out;
      BOOST_CHECK_NO_THROW(forthTask(ASCENDING, 25, out));
      double number;
      std::vector<double> numbers;
      for (int j = 0; j < 25; j++)
      {
        out >> number;
        numbers.push_back(number);
      }

      std::vector<double> sortedNumbers;
      for (int j = 0; j < 25; j++)
      {
        out >> number;
        sortedNumbers.push_back(number);
      }

      std::sort(numbers.begin(), numbers.end());
      for (unsigned long j = 0; j < sortedNumbers.size(); j++)
      {
        BOOST_CHECK_EQUAL(sortedNumbers[j], numbers[j]);
      }
    }
  }

BOOST_AUTO_TEST_SUITE_END()
