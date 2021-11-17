#include <iostream>
#include <fstream>
#include <cstring>
#include "task1.hpp"
#include "task2.hpp"

int main(int argc, char *argv[])
{
  try
  {
    if (argc != 2)
    {
      throw std::invalid_argument("The argument amount is invalid");
    }
    if (strcmp(argv[1], "1") == 0)
    {
      kosnitskiy::executeFirstTask(std::cin, std::cout);
    }
    else if (strcmp(argv[1], "2") == 0)
    {
      kosnitskiy::executeSecondTask(std::cin, std::cout);
    }
    else
    {
      throw std::invalid_argument("The argument contains improper information");
    }
  }
  catch (const std::invalid_argument &exc)
  {
    std::cerr << exc.what();
    return 1;
  }
}
