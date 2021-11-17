#include <iostream>
#include <sstream>
#include <algorithm>
#include "user-interface.hpp"
#include "factorial-container.hpp"

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    return 1;
  }
  std::stringstream s(argv[1]);
  unsigned int index = 0;
  s >> index;
  if (s.fail() || (s.rdbuf()->in_avail() != 0) || (index > 2) || (index == 0))
  {
    return 1;
  }
  switch (index)
  {
  case 1:
    kosnitskiy::UserInterface(std::cin, std::cout).processCommands();
    break;
  case 2:
  {
    kosnitskiy::Factorials factorials;
    std::copy(factorials.cbegin(), factorials.cend(),
              std::ostream_iterator<kosnitskiy::Factorials::value_type>(std::cout, " "));
    std::cout << '\n';
    std::copy(factorials.crbegin(), factorials.crend(),
              std::ostream_iterator<kosnitskiy::Factorials::value_type>(std::cout, " "));
    std::cout << '\n';
    break;
  }
  }
  return 0;
}
