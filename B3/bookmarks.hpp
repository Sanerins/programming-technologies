#ifndef B3_BOOKMARKS_HPP
#define B3_BOOKMARKS_HPP

#include <list>
#include <string>
#include <vector>
#include "phone-book.hpp"

namespace kosnitskiy
{
  struct Marker
  {
    std::string name;
    std::list<Phonebook::Dataset>::const_iterator mark;
  };

  class Markers
  {
  public:
    void pushBack(Marker mark);

    std::vector<Marker>::const_iterator end();
    std::vector<Marker>::const_iterator begin();

    std::vector<Marker>::const_iterator findBookmark(const std::string &name);

    void changeMark(std::vector<Marker>::const_iterator mark, std::list<Phonebook::Dataset>::const_iterator newMark);

  private:
    std::vector<Marker> bookmarks_;
  };
}
#endif //B3_BOOKMARKS_HPP
