#include <cstring>
#include <stdexcept>
#include <fstream>
#include "sstream"
#include "sortingDirection.hpp"
#include "firstTask.hpp"
#include "secondTask.hpp"
#include "thirdTask.hpp"
#include "forthTask.hpp"

using namespace kosnitskiy;

int main(int argc, char *argv[])
{
  try
  {
    if (argc < 2)
    {
      throw std::invalid_argument("Improper arguments");
    }

    unsigned int task = 0;
    {
      std::istringstream s(argv[1]);
      s >> task;
      if (s.fail() || !s.eof())
      {
          throw std::invalid_argument("Improper arguments");
      }
    }

    if ((task == 0) || (task > 4))
    {
      throw std::invalid_argument("Improper arguments");
    }

    switch (task)
    {
    case 1:
      if ((argc != 3))
      {
        throw std::invalid_argument("Improper arguments");
      }
      firstTask(getDirection(argv[2]));
      break;
    case 2:
    {
      if (argc != 3)
      {
        throw std::invalid_argument("Improper arguments");
      }
      std::ifstream file;
      file.open(argv[2]);
      if (!file.is_open())
      {
        throw std::invalid_argument("There is no such a file");
      }
      else if (file.fail())
      {
        throw std::invalid_argument("File is corrupted");
      }
      secondTask(file);
      break;
    }
    case 3:
      if (argc != 2)
      {
        throw std::invalid_argument("Improper arguments");
      }
      thirdTask();
      break;
    case 4:
    {
      if ((argc != 4))
      {
        throw std::invalid_argument("Improper arguments");
      }
      int size = 0;
      {
        std::istringstream s(argv[3]);
        s >> size;
        if (s.fail() || !s.eof())
        {
          throw std::invalid_argument("Improper arguments");
        }
      }

      if (size <= 0)
      {
        throw std::invalid_argument("Improper arguments");
      }

      srand(time(nullptr));
      forthTask(getDirection(argv[2]), size);
      break;
    }
    }
  }
  catch (const std::logic_error &except)
  {
    std::cerr << "Unexpected argument values exception" << '\n';
    std::cerr << "'" << except.what() << "' caused the problem\n";
    return 1;
  }
  catch (const std::runtime_error &except)
  {
    std::cerr << "Unexpected input values exception" << '\n';
    std::cerr << "'" << except.what() << "' caused the problem\n";
    return 1;
  }
  return 0;
}
