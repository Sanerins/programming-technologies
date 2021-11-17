#ifndef B4_UTILS_HPP
#define B4_UTILS_HPP

#include <string>
#include <iostream>

namespace kosnitskiy
{
  struct DataStruct
  {
    int key1;
    int key2;
    std::string str;
  };

  std::ostream &operator<<(std::ostream &out, const DataStruct &data);

  class DataReader
  {
  public:
    DataReader(DataStruct &data);

    friend std::istream &operator>>(std::istream &in, DataReader data);

  private:
    DataStruct &data_;
  };

  std::istream &operator>>(std::istream &in, DataReader data);

  std::istream &eatWhiteSpaces(std::istream &in);

  std::istream &eatNewLines(std::istream &in);
}

#endif //B4_UTILS_HPP
