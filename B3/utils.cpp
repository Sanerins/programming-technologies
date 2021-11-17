#include <string>
#include <iostream>
#include <limits>
#include "utils.hpp"

std::istream &operator>>(std::istream &in, Name sName)
{
  if(in.fail()) {
    return in;
  }
  std::string &name = sName.name_;
  in.get();
  while (in.peek() != '\n')
  {
    name.push_back(in.get());
  }
  if (name.empty() || name.at(0) != '"')
  {
    in.get();
    in.setstate(std::ios::failbit);
    return in;
  }
  name.erase(0, 1);

  if (name.at(0) == '"')
  {
    in.get();
    in.setstate(std::ios::failbit);
    return in;
  }

  //std::string::iterator
  for (auto letter = name.begin(); letter != name.end(); letter++)
  {
    if (*letter == '"')
    {
      if (*std::prev(letter) != '\\')
      {
        if (std::next(letter) != name.end())
        {
          in.get();
          in.setstate(std::ios::failbit);
          return in;
        }
        else
        {
          name.erase(letter);
          break;
        }
      }
      else
      {
        letter = name.erase(std::prev(letter));
      }
    }
  }
  return in;
}

Name::Name(std::string &name):
  name_(name)
{
}

std::istream &operator>>(std::istream &in, Number sNumber)
{
  if(in.fail()) {
    return in;
  }
  std::string &number = sNumber.number_;
  in >> number;
  if (number.find_first_not_of("0123456789") != std::string::npos)
  {
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    in.setstate(std::ios::failbit);
    return in;
  }
  return in;
}

Number::Number(std::string &num):
  number_(num)
{
}
