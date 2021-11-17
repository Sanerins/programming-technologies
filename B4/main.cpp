#include <vector>
#include <fstream>
#include "utils.hpp"
#include "algorithm.hpp"

int main()
{
  std::vector<kosnitskiy::DataStruct> vector;
  try
  {
    kosnitskiy::execute(vector, std::cin, std::cout);
  }
  catch (const std::invalid_argument &exc)
  {
    std::cerr << exc.what() << '\n';
    return 1;
  }
  return 0;
}
