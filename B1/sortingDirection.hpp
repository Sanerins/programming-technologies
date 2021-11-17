#ifndef B1_SORTINGDIRECTION_HPP
#define B1_SORTINGDIRECTION_HPP

namespace kosnitskiy
{
  enum SortingDirection
  {
    ASCENDING, DESCENDING,
  };

  SortingDirection getDirection(const char *src);
}

#endif //B1_SORTINGDIRECTION_HPP
