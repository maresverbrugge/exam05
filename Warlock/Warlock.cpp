#include "Warlock.hpp"

// default constructor
Warlock::Warlock()
{

}

// copy constructor
Warlock::Warlock(const Warlock& original)
{
  *this = original;
}

// copy assignment operator overload
Warlock& Warlock::operator=(const Warlock& original)
{
  this->_name = original._name;
  this->_title = original._title;
  return *this;
}

// destructor
Warlock::~Warlock()
{
  std::cout << getName() << ": My job here is done!" << std::endl;
}

// constructor overload
Warlock::Warlock(const std::string &name, const std::string &title) : _name(name), _title(title)
{
  std::cout << getName() << ": This looks like another boring day." << std::endl;
}

std::string const & Warlock::getName() const
{
  return(_name);
}

std::string const & Warlock::getTitle() const
{
  return(_title);
}

void Warlock::setTitle(const std::string& newTitle)
{
  _title = newTitle;
}

void Warlock::introduce() const
{
  std::cout << getName() << ": I am " << getName() << ", " << getTitle() << "!" << std::endl;
}
