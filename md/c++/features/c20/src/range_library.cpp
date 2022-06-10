#include <concepts>
#include <iostream>

//简化操作：
void simple_action()
{
  std::cout << "simple_action" << std::endl;
  std::vector<int> vec{3, 1, 2, 5, 6, 4};

  // std::sort()
  std::sort(vec.begin(), vec.end());
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>{cout, " "}); // 1 2 3 4 5 6

  // ranges::sort()
  std::ranges::sort(vec);
  std::ranges::copy(vec, std::ostream_iterator<int>{cout, " "}); // 1 2 3 4 5 6
}

//串联视图：
void view_action()
{
  std::cout << "view_action" << std::endl;
  std::vector<int> vec{1, 2, 3, 4, 5, 6};

  auto even = [](int i){ return i % 2 == 0; };
  auto square = [](int i){ return i * i; };

  auto result = vec | std::views::filter(even) | std::views::transform(square);
  /* 此时 result 并没有被计算，只是定义了一系列视图，只有到下面的遍历操作时，result 触发，即所谓延迟计算 */
  for (auto i : result)
  {
    cout << i << " "; // 4 16 36
  }
}

//过滤和变换：
void filter_transfrom_action()
{
  std::cout << "filter_transfrom_action" << std::endl;

  std::vector vec{1, 2, 3, 4, 5};

  auto result = vec | std::views::transform([](int i){ return i * i; }) | std::views::take(3);

  cout << std::accumulate(result.begin(), result.end(), 0) << endl; // 14
}

int main()
{
  simple_action();
  view_action();
  filter_transfrom_action();

  return 0;
}
