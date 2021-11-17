#include "forthTask.hpp"
#include <iostream>
#include <ctime>
#include <memory>
#include <forward_list>
#include <vector>
#include <iterator>
#include "bubbleSort.hpp"
#include "policy.hpp"
#include "sortingDirection.hpp"

void kosnitskiy::forthTask(const SortingDirection &args, int size, std::ostream &out)
{
  std::unique_ptr<double[]> array(new double[size]);
  fillRandom(array, size);
  std::vector<double> arrayVec(array.get(), (array.get() + size));
  std::copy(arrayVec.begin(), arrayVec.end(), std::ostream_iterator<double>(out, " "));
  out << '\n';
  BubbleSort::sort<std::vector<double>, IndexVectorPolicy<std::vector<double>>>(arrayVec, args);
  std::copy(arrayVec.begin(), arrayVec.end(), std::ostream_iterator<double>(out, " "));
}

void kosnitskiy::fillRandom(std::unique_ptr<double[]> &array, int size)
{
  for (int i = 0; i < size; i++)
  {
    array[i] = (rand() / double(RAND_MAX)) * 2 - 1;
  }
}
