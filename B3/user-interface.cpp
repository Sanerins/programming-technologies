#include "user-interface.hpp"
#include <string>
#include <limits>
#include <iostream>
#include <vector>
#include "utils.hpp"
#include "phone-book.hpp"

using namespace kosnitskiy;

kosnitskiy::UserInterface::UserInterface(std::istream &in, std::ostream &out):
  in_(&in),
  out_(&out)
{
  bookmarks_.pushBack({"current", phoneBook_.begin()});
}

void kosnitskiy::UserInterface::processCommands()
{
  std::string token = "";
  while (!in_->eof())
  {
    *in_ >> token;
    if (in_->eof())
    {
      continue;
    }
    else
    {
      //std::map<std::string, void (UserInterface::*)()>::iterator
      auto command = commands.find(token);
      if (command != commands.end())
      {
        (this->*(command->second))();
      }
      else
      {
        in_->ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        *out_ << "<INVALID COMMAND>\n";
      }
    }
  }
  if ((in_->fail() && !in_->eof()))
  {
    exit(2);
  }
}

void kosnitskiy::UserInterface::add()
{
  try
  {
    std::string name = "";
    std::string number = "";
    *in_ >> Number(number) >> Name(name);

    if(in_->fail()) {
      auto state = in_->rdstate();
      state &= ~std::ios_base::failbit;
      in_->clear(state);
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    else if (number.empty() || name.empty())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    else if ((in_->get() != '\n') && (!in_->eof()))
    {
      in_->ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    else
    {
      phoneBook_.add({number, name});
      reassignMarks();
    }
  }
  catch (const std::invalid_argument &exc)
  {
    *out_ << exc.what() << '\n';
  }
}

void kosnitskiy::UserInterface::store()
{
  std::string mark = "";
  *in_ >> mark;
  std::string newMark = "";
  *in_ >> newMark;
  if (mark.empty() || newMark.empty())
  {
    *out_ << "<INVALID COMMAND>\n";
  }
  else if ((in_->get() != '\n') && (!in_->eof()))
  {
    in_->ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  else
  {
    //std::vector<kosnitskiy::Marker>::iterator
    auto bookMark = bookmarks_.findBookmark(mark);
    if (bookMark == bookmarks_.end())
    {
      *out_ << "<INVALID BOOKMARK>\n";
    }
    else
    {
      bookmarks_.pushBack({newMark, bookMark->mark});
    }
  }
}

void UserInterface::insert()
{
  std::string token;
  *in_ >> token;
  if (token == "before")
  {
    insertBefore();
  }
  else if (token == "after")
  {
    insertAfter();
  }
  else
  {
    in_->ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    *out_ << "<INVALID COMMAND>\n";
  }
}

void kosnitskiy::UserInterface::insertBefore()
{
  std::string mark = "";
  *in_ >> mark;

  try
  {
    std::string name = "";
    std::string number = "";
    *in_ >> Number(number) >> Name(name);
    if(in_->fail()) {
      auto state = in_->rdstate();
      state &= ~std::ios_base::failbit;
      in_->clear(state);
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    else if (number.empty() || name.empty() || mark.empty())
    {
      *out_ << "<INVALID COMMAND>\n";
    }
    else if ((in_->get() != '\n') && (!in_->eof()))
    {
      in_->ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      *out_ << "<INVALID COMMAND>\n";
    }
    else
    {
      //std::vector<kosnitskiy::Marker>::iterator
      auto bookMark = bookmarks_.findBookmark(mark);
      if (bookMark == bookmarks_.end())
      {
        *out_ << "<INVALID BOOKMARK>\n";
      }
      else
      {
        if (phoneBook_.empty())
        {
          phoneBook_.add({number, name});
          reassignMarks();
        }
        else
        {
          phoneBook_.addBack(bookMark->mark, {number, name});
        }
      }
    }
  }
  catch (const std::invalid_argument &exc)
  {
    *out_ << exc.what() << '\n';
  }
}

void kosnitskiy::UserInterface::insertAfter()
{
  std::string mark = "";
  *in_ >> mark;

  try
  {
    std::string name = "";
    std::string number = "";
    *in_ >> Number(number) >> Name(name);
    if(in_->fail()) {
      auto state = in_->rdstate();
      state &= ~std::ios_base::failbit;
      in_->clear(state);
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    else if (number.empty() || name.empty() || mark.empty())
    {
      *out_ << "<INVALID COMMAND>\n";
    }
    else if ((in_->get() != '\n') && (!in_->eof()))
    {
      in_->ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      *out_ << "<INVALID COMMAND>\n";
    }
    else
    {
      //std::vector<kosnitskiy::Marker>::iterator
      auto bookMark = bookmarks_.findBookmark(mark);
      if (bookMark == bookmarks_.end())
      {
        *out_ << "<INVALID BOOKMARK>\n";
      }
      else
      {
        if (phoneBook_.empty())
        {
          phoneBook_.add({number, name});
          reassignMarks();
        }
        else
        {
          phoneBook_.addForward(bookMark->mark, {number, name});
        }
      }
    }
  }
  catch (const std::invalid_argument &exc)
  {
    *out_ << exc.what() << '\n';
  }
}

void kosnitskiy::UserInterface::deleteMark()
{
  std::string mark = "";
  *in_ >> mark;

  if (mark.empty())
  {
    *out_ << "<INVALID COMMAND>\n";
  }
  else if ((in_->get() != '\n') && (!in_->eof()))
  {
    in_->ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    *out_ << "<INVALID COMMAND>\n";
  }
  else
  {
    //std::vector<kosnitskiy::Marker>::iterator
    auto bookMark = bookmarks_.findBookmark(mark);
    if (bookMark == bookmarks_.end())
    {
      *out_ << "<INVALID BOOKMARK>\n";
    }
    else
    {
      bookmarks_.changeMark(bookMark, phoneBook_.remove(bookMark->mark));
      //std::_List_iterator<Phonebook::Dataset>
      auto oldMark = bookMark->mark;
      if (bookMark->mark == phoneBook_.end() && !phoneBook_.empty())
      {
        bookmarks_.changeMark(bookMark, std::prev(bookMark->mark));
      }
      for(auto i = bookmarks_.begin(); i != bookmarks_.end(); i++)
      {
        if (oldMark == bookMark->mark)
        {
          bookmarks_.changeMark(i, bookMark->mark);
        }
      }
    }
  }
}

void kosnitskiy::UserInterface::show()
{
  std::string mark = "";
  *in_ >> mark;

  if (mark.empty())
  {
    *out_ << "<INVALID COMMAND>\n";
  }
  else if ((in_->get() != '\n') && (!in_->eof()))
  {
    in_->ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    *out_ << "<INVALID COMMAND>\n";
  }
  else
  {
    //std::vector<kosnitskiy::Marker>::iterator
    auto bookMark = bookmarks_.findBookmark(mark);
    if (bookMark == bookmarks_.end())
    {
      *out_ << "<INVALID BOOKMARK>\n";
    }
    else
    {
      try
      {
        Phonebook::Dataset &data = phoneBook_.get(bookMark->mark);
        *out_ << data.number << " " << data.name << "\n";
      }
      catch (const std::out_of_range &range)
      {
        *out_ << "<EMPTY>\n";
      }
    }
  }
}

void kosnitskiy::UserInterface::move()
{
  std::string mark = "";
  *in_ >> mark;
  std::string distance = "";
  *in_ >> distance;
  if (mark.empty() || distance.empty())
  {
    *out_ << "<INVALID COMMAND>\n";
    return;
  }
  else if ((in_->get() != '\n') && (!in_->eof()))
  {
    in_->ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    *out_ << "<INVALID COMMAND>\n";
    return;
  }
  //std::vector<kosnitskiy::Marker>::iterator
  auto bookMark = bookmarks_.findBookmark(mark);
  if (bookMark == bookmarks_.end())
  {
    *out_ << "<INVALID BOOKMARK>\n";
  }
  else if (phoneBook_.empty())
  {
    bookmarks_.changeMark(bookMark, phoneBook_.begin());
  }
  else if (distance == "last")
  {
    bookmarks_.changeMark(bookMark, std::prev(phoneBook_.end()));
  }
  else if (distance == "first")
  {
    bookmarks_.changeMark(bookMark, phoneBook_.begin());
  }
  else if (distance.find_first_not_of("+-0123456789") == std::string::npos)
  {
    try
    {
      bookmarks_.changeMark(bookMark, phoneBook_.move(bookMark->mark, std::atol(distance.c_str())));
    }
    catch (const std::out_of_range &exc)
    {
      *out_ << "<INVALID STEP>\n";
    }
  }
  else
  {
    *out_ << "<INVALID STEP>\n";
    return;
  }
}

void UserInterface::reassignMarks()
{
  if (phoneBook_.size() == 1)
  {
    for(auto curr = bookmarks_.begin(); curr != bookmarks_.end(); curr++)
    {
      bookmarks_.changeMark(curr, phoneBook_.begin());
    }
  }
}

void UserInterface::setInStream(std::istream &in)
{
  in_ = &in;
}

void UserInterface::setOutStream(std::ostream &out)
{
  out_ = &out;
}
