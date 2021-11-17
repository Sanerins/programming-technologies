#ifndef B1_BUBBLESORT_HPP
#define B1_BUBBLESORT_HPP

#include <string>
#include <forward_list>
#include <vector>
#include "sortingDirection.hpp"

namespace kosnitskiy
{
  class BubbleSort
  {
  public:
    template<class T, class Policy>
    static void sort(T &arr, const SortingDirection &param)
    {
      if (Policy::begin(arr) == Policy::end(arr))
      {
        return;
      }
      for (auto i = Policy::next(Policy::begin(arr)); i != Policy::end(arr); i++)
      {
        for (auto j = Policy::begin(arr); j != i; j++)
        {
          if (param == ASCENDING)
          {
            if (Policy::get(arr, i) < Policy::get(arr, j))
            {
              std::swap(Policy::get(arr, i), Policy::get(arr, j));
            }
          }
          else
          {
            if (Policy::get(arr, i) > Policy::get(arr, j))
            {
              std::swap(Policy::get(arr, i), Policy::get(arr, j));
            }
          }
        }
      }
    }
  };
}
#endif //B1_BUBBLESORT_HPP
