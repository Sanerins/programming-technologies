#include "task1.hpp"
#include <iostream>
#include <unordered_set>
#include <string>
#include <iterator>

void kosnitskiy::executeFirstTask(std::istream &in, std::ostream &out)
{
  std::unordered_set<std::string> dictionary;
  kosnitskiy::parseWords(dictionary, in);
  std::copy(dictionary.begin(), dictionary.end(), std::ostream_iterator<std::string>(out, "\n"));
}

void kosnitskiy::parseWords(std::unordered_set<std::string> &strings, std::istream &in)
{
  strings.insert(std::istream_iterator<std::string>(in), std::istream_iterator<std::string>());
  if (in.fail() && !in.eof())
  {
    throw std::invalid_argument("File contains invalid information");
  }
}
