#ifndef B1_FORTHTASK_HPP
#define B1_FORTHTASK_HPP

#include <iostream>
#include <memory>
#include "sortingDirection.hpp"

namespace kosnitskiy
{
  void forthTask(const SortingDirection &args, int size, std::ostream &out = std::cout);

  void fillRandom(std::unique_ptr<double[]> &array, int size);
}

#endif //B1_FORTHTASK_HPP
