#include "firstTask.hpp"
#include <iostream>
#include <forward_list>
#include <vector>
#include <exception>
#include <iterator>
#include "sortingDirection.hpp"
#include "bubbleSort.hpp"
#include "policy.hpp"

void kosnitskiy::firstTask(const SortingDirection &arg1, std::istream &in, std::ostream &out)
{
  std::vector<long> infoVectorFirst;

  while (in)
  {
    long temp;
    in >> temp;
    if (in.fail() && !in.eof())
    {
      throw std::runtime_error("Incorrect input");
    }
    else if(!in.eof())
    {
      infoVectorFirst.push_back(temp);
    }
  }

  if (in.bad())
  {
    throw std::runtime_error("Incorrect input");
  }

  std::vector<long> infoVectorSecond = infoVectorFirst;

  std::forward_list<long> infoList(infoVectorFirst.begin(), infoVectorFirst.end());

  BubbleSort::sort<std::vector<long>, IndexVectorPolicy<std::vector<long>>>(infoVectorFirst, arg1);
  BubbleSort::sort<std::vector<long>, AtVectorPolicy<std::vector<long>>>(infoVectorSecond, arg1);
  BubbleSort::sort<std::forward_list<long>, ListPolicy<std::forward_list<long>>>(infoList, arg1);

  std::copy(infoVectorFirst.begin(), infoVectorFirst.end(), std::ostream_iterator<long>(out, " "));
  out << "\n";
  std::copy(infoVectorSecond.begin(), infoVectorSecond.end(), std::ostream_iterator<long>(out, " "));
  out << "\n";
  std::copy(infoList.begin(), infoList.end(), std::ostream_iterator<long>(out, " "));
  out << "\n";
}
