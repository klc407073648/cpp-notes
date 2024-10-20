// 编写一个计算斐波那契数列的模板类
template <int N>
struct Fibonacci {
  static constexpr int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};

template <>
struct Fibonacci<0> {
  static constexpr int value = 0;
};

template <>
struct Fibonacci<1> {
  static constexpr int value = 1;
};

constexpr int fib = Fibonacci<10>::value;

// 实现一个计算阶乘的函数模板
template <int N>
constexpr int factorial() {
  return N * factorial<N - 1>();
}

template <>
constexpr int factorial<0>() {
  return 1;
}