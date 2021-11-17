#include "utils.hpp"
#include <istream>

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
