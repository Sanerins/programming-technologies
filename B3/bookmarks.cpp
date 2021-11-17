#include "bookmarks.hpp"

void kosnitskiy::Markers::pushBack(kosnitskiy::Marker mark)
{
  bookmarks_.push_back(mark);
}

std::vector<kosnitskiy::Marker>::const_iterator kosnitskiy::Markers::end()
{
  return bookmarks_.end();
}

std::vector<kosnitskiy::Marker>::const_iterator kosnitskiy::Markers::begin()
{
  return bookmarks_.begin();
}

std::vector<kosnitskiy::Marker>::const_iterator kosnitskiy::Markers::findBookmark(const std::string &name)
{
  //std::vector<kosnitskiy::Marker>::iterator
  for (auto i = bookmarks_.begin(); i != bookmarks_.end(); i++)
  {
    if (i->name == name)
    {
      return i;
    }
  }
  return bookmarks_.end();
}

void kosnitskiy::Markers::changeMark(std::vector<kosnitskiy::Marker>::const_iterator mark,
                                                                                std::list<kosnitskiy::Phonebook::Dataset>::const_iterator newMark)
{
  auto chMark = bookmarks_.erase(mark, mark);
  chMark->mark = newMark;
}
