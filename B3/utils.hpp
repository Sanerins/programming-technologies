#ifndef B3_UTILS_HPP
#define B3_UTILS_HPP

#include <string>
#include <iostream>

class Name
{
public:
  Name(std::string &name);

  friend std::istream &operator>>(std::istream &in, Name sName);

private:
  std::string &name_;
};

class Number
{
public:
  Number(std::string &num);

  friend std::istream &operator>>(std::istream &in, Number sNumber);

private:
  std::string &number_;
};

#endif //B3_UTILS_HPP
