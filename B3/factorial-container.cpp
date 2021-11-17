#include "factorial-container.hpp"
#include <cassert>

kosnitskiy::Factorials::Iterator::Iterator():
  currPosition_(endIndex),
  result_(-1)
{}

kosnitskiy::Factorials::Iterator::Iterator(int index, int value):
  currPosition_(index),
  result_(value)
{}

kosnitskiy::Factorials::reference kosnitskiy::Factorials::Iterator::operator*() const noexcept
{
  return result_;
}

kosnitskiy::Factorials::Iterator &kosnitskiy::Factorials::Iterator::operator++()
{
  assert(currPosition_ != endIndex);
  currPosition_++;
  result_ *= currPosition_;
  return *this;
}

kosnitskiy::Factorials::Iterator kosnitskiy::Factorials::Iterator::operator++(int)
{
  Iterator temp = *this;
  ++(*this);
  return temp;
}

kosnitskiy::Factorials::Iterator &kosnitskiy::Factorials::Iterator::operator--()
{
  assert(currPosition_ != beginIndex);
  result_ /= currPosition_;
  currPosition_--;
  return *this;
}

kosnitskiy::Factorials::Iterator kosnitskiy::Factorials::Iterator::operator--(int)
{
  Iterator temp = *this;
  --(*this);
  return temp;
}

constexpr int kosnitskiy::Factorials::Iterator::getFactorial(int number) noexcept
{
  int factorial = 1;
  for (int i = 2; i <= number; i++)
  {
    factorial *= i;
  }
  return factorial;
}

bool kosnitskiy::Factorials::Iterator::operator==(const kosnitskiy::Factorials::Iterator &src) const
{
  return this->currPosition_ == src.currPosition_;
}

bool kosnitskiy::Factorials::Iterator::operator!=(const kosnitskiy::Factorials::Iterator &src) const
{
  return this->currPosition_ != src.currPosition_;
}

kosnitskiy::Factorials::Iterator kosnitskiy::Factorials::cbegin() const noexcept
{
  return kosnitskiy::Factorials::Iterator(beginIndex, Iterator::getFactorial(beginIndex));
}

kosnitskiy::Factorials::Iterator kosnitskiy::Factorials::cend() const noexcept
{
  return kosnitskiy::Factorials::Iterator(endIndex, Iterator::getFactorial(endIndex));
}

kosnitskiy::Factorials::size_type kosnitskiy::Factorials::size() const noexcept
{
  return endIndex - beginIndex;
}

kosnitskiy::Factorials::const_reverse_iterator kosnitskiy::Factorials::crbegin() const noexcept
{
  return std::make_reverse_iterator(cend());
}

kosnitskiy::Factorials::const_reverse_iterator kosnitskiy::Factorials::crend() const noexcept
{
  return std::make_reverse_iterator(cbegin());
}

kosnitskiy::Factorials::size_type kosnitskiy::Factorials::max_size() const noexcept
{
  return endIndex - beginIndex;
}

bool kosnitskiy::Factorials::empty() const noexcept
{
  return false;
}

void kosnitskiy::Factorials::swap(kosnitskiy::Factorials &/*src*/) const noexcept
{
}

bool kosnitskiy::Factorials::operator==(const kosnitskiy::Factorials &) const noexcept
{
  return true;
}

bool kosnitskiy::Factorials::operator!=(const kosnitskiy::Factorials &src) const noexcept
{
  return !(*this == src);
}

bool kosnitskiy::Factorials::operator<(const kosnitskiy::Factorials &) const noexcept
{
  return false;
}

bool kosnitskiy::Factorials::operator>(const kosnitskiy::Factorials &) const noexcept
{
  return false;
}

bool kosnitskiy::Factorials::operator<=(const kosnitskiy::Factorials &) const noexcept
{
  return true;
}

bool kosnitskiy::Factorials::operator>=(const kosnitskiy::Factorials &) const noexcept
{
  return true;
}

kosnitskiy::Factorials::const_iterator kosnitskiy::Factorials::begin() const noexcept
{
  return kosnitskiy::Factorials::Iterator(beginIndex, Iterator::getFactorial(beginIndex));
}

kosnitskiy::Factorials::const_iterator kosnitskiy::Factorials::end() const noexcept
{
  return kosnitskiy::Factorials::Iterator(endIndex, Iterator::getFactorial(endIndex));
}

kosnitskiy::Factorials::const_reverse_iterator kosnitskiy::Factorials::rbegin() const noexcept
{
  return kosnitskiy::Factorials::const_reverse_iterator(end());
}

kosnitskiy::Factorials::const_reverse_iterator kosnitskiy::Factorials::rend() const noexcept
{
  return kosnitskiy::Factorials::const_reverse_iterator(begin());
}
