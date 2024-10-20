#include <utility>
#include <string>
#include <iostream>
class Person
{
private:
  std::string name;

public:
  // constructor for passed initial name:
  explicit Person(std::string const &n) : name(n)
  {
    std::cout << "copying string-CONSTR for " << name << std::endl;
  }
  explicit Person(std::string &&n) : name(std::move(n))
  {
    std::cout << "moving string-CONSTR for " << name << std::endl;
  }
  // copy and move constructor:
  Person(Person const &p) : name(p.name)
  {
    std::cout << "COPY-CONSTR Person " << name << std::endl;
  }
  Person(Person &&p) : name(std::move(p.name))
  {
    std::cout << "MOVE-CONSTR Person " << name << std::endl;
  }
};
int main()
{
  std::string s = "sname";
  Person p1(s);             // init with string object => calls copying
  Person p2("tmp");         // init with string literal => calls moving
  Person p3(p1);            // copy Person => calls COPY-CONSTR
  Person p4(std::move(p1)); // move Person => calls MOVE-CONST
  return 0;
}
