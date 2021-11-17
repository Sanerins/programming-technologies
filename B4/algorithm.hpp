#ifndef B4_ALGORITHM_HPP
#define B4_ALGORITHM_HPP

#include <vector>
#include <iostream>
#include "utils.hpp"

namespace kosnitskiy
{
  void execute(std::vector<DataStruct> &vector, std::istream &in, std::ostream &out);

  void read(std::vector<DataStruct> &vector, std::istream &in);

  void sort(std::vector<DataStruct> &vector);

  void print(std::vector<DataStruct> &vector, std::ostream &out);
}

#endif //B4_ALGORITHM_HPP
