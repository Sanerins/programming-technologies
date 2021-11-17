#include "utils.hpp"
#include <string>
#include <iostream>
#include <exception>
#include <algorithm>

std::ostream &kosnitskiy::operator<<(std::ostream &out, const DataStruct &data)
{
  out << data.key1 << ',' << data.key2 << ',' << data.str;
  return out;
}

std::istream &kosnitskiy::operator>>(std::istream &in, kosnitskiy::DataReader data)
{
  char delim1;
  char delim2;
  in >> std::noskipws >> eatNewLines;
  if (in.eof())
  {
    return in;
  }
  in >> data.data_.key1 >> eatWhiteSpaces >> delim1 >> eatWhiteSpaces >> data.data_.key2 >> eatWhiteSpaces >> delim2 >> eatWhiteSpaces;
  std::getline(in, data.data_.str, '\n');
  if ((in.fail() && !in.eof()) || std::abs(data.data_.key1) > 5 || std::abs(data.data_.key2) > 5 || delim1 != ',' || delim2 != ',' ||
      data.data_.str.empty())
  {
    in.clear();
    in.setstate(std::ios::failbit);
  }
  else
  {
    in.clear();
  }
  return in;
}

kosnitskiy::DataReader::DataReader(kosnitskiy::DataStruct &data):
  data_(data)
{
}

std::istream &kosnitskiy::eatWhiteSpaces(std::istream &in)
{
  if (in.fail())
  {
    return in;
  }
  while (in.peek() == ' ' || in.peek() == '\t')
  {
    in.get();
  }
  if (in.fail() && !in.eof())
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream &kosnitskiy::eatNewLines(std::istream &in)
{
  if (in.fail())
  {
    return in;
  }
  while (in.peek() == '\n' || in.peek() == '\t' || in.peek() == ' ')
  {
    in.get();
  }
  if (in.fail() && !in.eof())
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

