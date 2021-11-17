#include <stdexcept>
#include "phone-book.hpp"

kosnitskiy::Phonebook::Dataset &kosnitskiy::Phonebook::get(const std::list<kosnitskiy::Phonebook::Dataset>::const_iterator iter)
{
  if (iter == dataBase_.end())
  {
    throw std::out_of_range("Unexpected iterator");
  }
  return *(dataBase_.erase(iter, iter));
}

std::list<kosnitskiy::Phonebook::Dataset>::const_iterator
kosnitskiy::Phonebook::replace(std::list<kosnitskiy::Phonebook::Dataset>::const_iterator iter, Dataset item)
{
  auto innerIter = dataBase_.erase(iter, iter);
  innerIter->name = item.name;
  innerIter->number = item.number;
  return iter;
}

void kosnitskiy::Phonebook::add(kosnitskiy::Phonebook::Dataset item)
{
  dataBase_.push_back(item);
}

std::list<kosnitskiy::Phonebook::Dataset>::const_iterator
kosnitskiy::Phonebook::addBack(const std::list<kosnitskiy::Phonebook::Dataset>::const_iterator iter, Dataset item)
{
  dataBase_.insert(iter, item);
  return (std::prev(iter));
}

std::list<kosnitskiy::Phonebook::Dataset>::const_iterator
kosnitskiy::Phonebook::addForward(std::list<kosnitskiy::Phonebook::Dataset>::const_iterator iter, Dataset item)
{
  iter++;
  addBack(iter, item);
  move(iter, -2);
  return (std::next(iter));
}

std::list<kosnitskiy::Phonebook::Dataset>::const_iterator
kosnitskiy::Phonebook::moveBack(std::list<kosnitskiy::Phonebook::Dataset>::const_iterator iter)
{
  if (iter == dataBase_.begin())
  {
    throw std::out_of_range("Iterator can't be moved any further in_ that direction");
  }
  iter--;
  return iter;
}

std::list<kosnitskiy::Phonebook::Dataset>::const_iterator
kosnitskiy::Phonebook::moveForward(std::list<kosnitskiy::Phonebook::Dataset>::const_iterator iter)
{
  iter++;
  if (iter == dataBase_.end())
  {
    iter--;
    throw std::out_of_range("Iterator can't be moved any further in that direction");
  }
  return iter;
}

std::list<kosnitskiy::Phonebook::Dataset>::const_iterator
kosnitskiy::Phonebook::move(std::list<kosnitskiy::Phonebook::Dataset>::const_iterator iter, long destination)
{
  if ((destination < 0) && (std::distance(dataBase_.cbegin(), iter) < (-destination)))
  {
    throw std::out_of_range("Iterator can't be moved so far in that direction");
  }
  else if ((destination > 0) && (std::distance(iter, dataBase_.cend()) < destination))
  {
    throw std::out_of_range("Iterator can't be moved so far in that direction");
  }
  std::advance(iter, destination);
  return iter;
}

std::list<kosnitskiy::Phonebook::Dataset>::const_iterator
kosnitskiy::Phonebook::remove(const std::list<kosnitskiy::Phonebook::Dataset>::const_iterator iter)
{
  return dataBase_.erase(iter);
}

std::list<kosnitskiy::Phonebook::Dataset>::const_iterator kosnitskiy::Phonebook::begin()
{
  return dataBase_.begin();
}

std::list<kosnitskiy::Phonebook::Dataset>::const_iterator kosnitskiy::Phonebook::end()
{
  return dataBase_.end();
}

bool kosnitskiy::Phonebook::empty()
{
  return dataBase_.empty();
}

size_t kosnitskiy::Phonebook::size()
{
  return dataBase_.size();
}
