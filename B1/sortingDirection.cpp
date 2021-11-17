#include "sortingDirection.hpp"
#include <cstring>
#include <stdexcept>

kosnitskiy::SortingDirection kosnitskiy::getDirection(const char *src)
{
  if ((std::strcmp(src, "ascending") != 0) && (std::strcmp(src, "descending") != 0))
  {
    throw std::invalid_argument("Improper arguments");
  }
  if ((std::strcmp(src, "ascending") == 0))
  {
    return ASCENDING;
  }
  return DESCENDING;
}
