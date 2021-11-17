#include <algorithm>
#include <iterator>
#include "algorithm.hpp"

void kosnitskiy::execute(std::vector<DataStruct> &vector, std::istream &in, std::ostream &out)
{
  read(vector, in);
  sort(vector);
  print(vector, out);
}

void kosnitskiy::read(std::vector<DataStruct> &vector, std::istream &in)
{
  while (!in.eof())
  {
    DataStruct structure;
    in >> DataReader(structure);
    if (in.fail() && !in.eof())
    {
      throw std::invalid_argument("Something bad happened");
    }
    if (!in.eof())
    {
      vector.push_back(structure);
    }
  }
}

bool comparator(kosnitskiy::DataStruct &left, kosnitskiy::DataStruct &right)
{
  if (left.key1 != right.key1)
  {
    return left.key1 < right.key1;
  }
  else if (left.key2 != right.key2)
  {
    return left.key2 < right.key2;
  }
  else
  {
    return left.str.size() < right.str.size();
  }
}

void kosnitskiy::sort(std::vector<DataStruct> &vector)
{
  std::sort(vector.begin(), vector.end(), comparator);
}

void kosnitskiy::print(std::vector<DataStruct> &vector, std::ostream &out)
{
  copy(vector.begin(), vector.end(), std::ostream_iterator<DataStruct>(out, "\n"));
}
