#ifndef B5_TASK1_HPP
#define B5_TASK1_HPP

#include <string>
#include <istream>
#include <unordered_set>

namespace kosnitskiy
{
  void executeFirstTask(std::istream &in, std::ostream &out);

  void parseWords(std::unordered_set<std::string> &strings, std::istream &in);
}

#endif //B5_TASK1_HPP
