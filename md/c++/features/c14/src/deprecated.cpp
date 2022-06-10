#include <cmath>
#include <iostream>
using namespace std;

void [[deprecated]] fun(){};

int main()
{
  /*
  fun.cpp:6:6: warning: attribute ignored [-Wattributes]
    6 | void [[deprecated]] fun(){};
      |      ^
  fun.cpp:6:6: note: an attribute that appertains to a type-specifier is ignored
  */
  fun();
  return 0;
}
