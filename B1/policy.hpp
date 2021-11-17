#ifndef B1_POLICY_HPP
#define B1_POLICY_HPP

#include <forward_list>
#include <utility>
#include <vector>
#include <stdexcept>

namespace kosnitskiy
{
  template<class T>
  struct IndexVectorPolicy
  {
    static size_t begin(T &/*src*/)
    {
      return 0;
    }

    static size_t end(T &src)
    {
      return src.size();
    }

    static size_t next(size_t index)
    {
      return index + 1;
    }

    static typename T::value_type &get(T &src, size_t index)
    {
      return src[index];
    }
  };

  template<class T>
  struct AtVectorPolicy
  {
    static size_t begin(T &/*src*/)
    {
      return 0;
    }

    static size_t end(T &src)
    {
      return src.size();
    }

    static size_t next(size_t index)
    {
      return index + 1;
    }

    static typename T::value_type &get(T &src, size_t index)
    {
      return src.at(index);
    }
  };

  template<class T>
  struct ListPolicy
  {
    static typename T::iterator begin(T &src)
    {
      return src.begin();
    }

    static typename T::iterator end(T &src)
    {
      return src.end();
    }

    static typename T::iterator next(typename T::iterator index)
    {
      return std::next(index);
    }

    static typename T::value_type &get(T &/*src*/, typename T::iterator &index)
    {
      return *index;
    }
  };
}

#endif //B1_POLICY_HPP
