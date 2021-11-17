#ifndef B3_USER_INTERFACE_HPP
#define B3_USER_INTERFACE_HPP

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "bookmarks.hpp"
#include "phone-book.hpp"

namespace kosnitskiy
{
  class UserInterface
  {
  public:
    UserInterface(std::istream &in, std::ostream &out);

    void setInStream(std::istream &in);
    void setOutStream(std::ostream &out);

    void processCommands();

  private:
    std::istream *in_;
    std::ostream *out_;
    Phonebook phoneBook_;
    Markers bookmarks_;
    const std::map<std::string, void (UserInterface::*)()> commands = {{"add",    &UserInterface::add},
                                                                       {"store",  &UserInterface::store},
                                                                       {"insert", &UserInterface::insert},
                                                                       {"delete", &UserInterface::deleteMark},
                                                                       {"show",   &UserInterface::show},
                                                                       {"move",   &UserInterface::move},};

    void add();

    void store();

    void insert();

    void insertBefore();

    void insertAfter();

    void deleteMark();

    void show();

    void move();

    void reassignMarks();
  };
}

#endif //B3_USER_INTERFACE_HPP
