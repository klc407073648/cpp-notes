#include <algorithm>
#include <iostream>
#include <vector>

template <int Val, typename T>
T addValue(T x)
{
  return x + Val;
}

int main()
{
  std::vector<int> source{1, 2, 3, 4, 5};
  std::vector<int> dest(5,0);

  std::transform(source.begin(), source.end(), dest.begin(), addValue<5, int>);

  for (std::vector<int>::iterator it = dest.begin(); it != dest.end(); ++it)
    std::cout << ' ' << *it; // 6 7 8 9 10
  std::cout << std::endl;

  return 0;
}
