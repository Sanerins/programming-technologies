#include "thirdTask.hpp"
#include <iostream>
#include <forward_list>
#include <vector>
#include <iterator>

void kosnitskiy::thirdTask(std::istream &in, std::ostream &out)
{
  std::vector<long> data;
  long temp = 1;
  while ((temp != 0))
  {
    in >> temp;
    if (in.eof())
    {
      break;
    }
    if (in.fail())
    {
      throw std::runtime_error("Incorrect input");
    }
    else
    {
      data.push_back(temp);
    }
  }
  if (data.empty())
  {
    return;
  }
  if (data[data.size() - 1] != 0)
  {
    throw std::logic_error("There is no 0 in the end");
  }
  data.pop_back();
  switch (*std::prev(data.end()))
  {
  case 1:
  {
    for (auto i = data.begin(); i != data.end(); i++)
    {
      if ((*i % 2) == 0)
      {
        i = data.erase(i);
        i = std::prev(i);
      }
    }
    break;
  }
  case 2:
  {
    for (auto i = data.begin(); i != data.end(); i++)
    {
      if ((*i % 3) == 0)
      {
        i = data.insert(++i, 3, 1);
      }
    }
    break;
  }
  }
  std::copy(data.begin(), data.end(), std::ostream_iterator<long>(out, " "));
}
