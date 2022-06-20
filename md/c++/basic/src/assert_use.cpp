#include <stdio.h>
#include <assert.h>

int main()
{
  int x = 7;

  /*  中间的一些大代码假设x意外地变成了9 */
  x = 9;

  // 程序员假设x在其余代码中为7
  assert(x == 7); // assert_use: assert_use.cpp:13: int main(): Assertion `x == 7' failed. Aborted

  /* 其余代码 */
  return 0;
}
