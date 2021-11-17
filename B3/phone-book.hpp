#ifndef B3_PHONE_BOOK_HPP
#define B3_PHONE_BOOK_HPP

#include <list>
#include <string>

namespace kosnitskiy
{
  class Phonebook
  {
  public:
    struct Dataset
    {
      std::string number;
      std::string name;
    };

    void add(Dataset item);
    Dataset &get(std::list<Dataset>::const_iterator iter);
    std::list<Dataset>::const_iterator replace(std::list<Dataset>::const_iterator iter, Dataset item);
    std::list<Dataset>::const_iterator remove(std::list<Dataset>::const_iterator iter);
    std::list<Dataset>::const_iterator addBack(std::list<Dataset>::const_iterator iter, Dataset item);
    std::list<Dataset>::const_iterator addForward(std::list<Dataset>::const_iterator iter, Dataset item);
    std::list<Dataset>::const_iterator moveBack(std::list<Dataset>::const_iterator iter);
    std::list<Dataset>::const_iterator moveForward(std::list<Dataset>::const_iterator iter);
    std::list<Dataset>::const_iterator move(std::list<Dataset>::const_iterator iter, long destination);

    std::list<Dataset>::const_iterator begin();
    std::list<Dataset>::const_iterator end();

    bool empty();
    size_t size();

  private:
    std::list<Dataset> dataBase_;
  };
}

#endif //B3_PHONE_BOOK_HPP
