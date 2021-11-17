#include "secondTask.hpp"
#include <iostream>
#include <fstream>
#include <memory>
#include <forward_list>
#include <vector>
#include <iterator>

void kosnitskiy::secondTask(std::ifstream &file, std::ostream &out)
{
  const unsigned int SIZE = 1000;
  std::streamsize expansion = 0;
  std::unique_ptr<char[], void (*)(void *)> info(static_cast<char *>(malloc(SIZE * sizeof(char))), std::free);
  while (file)
  {
    file.read(info.get() + expansion, SIZE);
    expansion += file.gcount();
    if (file.good())
    {
      std::unique_ptr<char[], void (*)(void *)> temp(static_cast<char *>(realloc(info.get(), SIZE + expansion)), std::free);
      info.release();
      info = std::move(temp);
    }
    else if (file.fail() && !file.eof())
    {
      throw std::runtime_error("Input is incorrect");
    }
  }
  file.close();
  if (expansion == 0)
  {
    return;
  }

  std::vector<char> infoVector(info.get(), (info.get() + expansion));

  out.write(infoVector.data(), expansion);
}
