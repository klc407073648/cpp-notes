#include <iostream>
#include <mutex>
#include <memory>
#include <thread>
#include <shared_mutex>
#include <array>
#include <tuple>
#include <utility>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <string>
#include <iterator>

struct A
{
};

void make_unique_fun()
{
	std::cout << "make_unique_fun" << std::endl;

	std::unique_ptr<A> ptr = std::make_unique<A>();
}

class ThreadSafe
{
public:
	ThreadSafe() { _value = 0; }

	int get() const
	{
		std::shared_lock<std::shared_timed_mutex> loc(_mutex);
		return _value;
	}

	void increase()
	{
		std::unique_lock<std::shared_timed_mutex> lock(_mutex);
		_value += 1;
	}

private:
	mutable std::shared_timed_mutex _mutex;
	int _value;
};

void threadSafe_fun()
{
	std::cout << "threadSafe_fun" << std::endl;

	auto thread = new ThreadSafe();
	thread->increase();
	thread->increase();
	std::cout << "thread->get:" << thread->get() << std::endl;
}

template <typename T, T... ints>
void print_sequence(std::integer_sequence<T, ints...> int_seq)
{
	std::cout << "The sequence of size " << int_seq.size() << ": ";
	((std::cout << ints << ' '), ...);
	std::cout << '\n';
}

// 转换数组为 tuple
template <typename Array, std::size_t... I>
auto a2t_impl(const Array &a, std::index_sequence<I...>)
{
	return std::make_tuple(a[I]...);
}

template <typename T, std::size_t N, typename Indices = std::make_index_sequence<N>>
auto a2t(const std::array<T, N> &a)
{
	return a2t_impl(a, Indices{});
}

// 漂亮地打印 tuple

template <class Ch, class Tr, class Tuple, std::size_t... Is>
void print_tuple_impl(std::basic_ostream<Ch, Tr> &os, const Tuple &t, std::index_sequence<Is...>)
{
	((os << (Is == 0 ? "" : ", ") << std::get<Is>(t)), ...);
}

template <class Ch, class Tr, class... Args>
auto &operator<<(std::basic_ostream<Ch, Tr> &os, const std::tuple<Args...> &t)
{
	os << "(";
	print_tuple_impl(os, t, std::index_sequence_for<Args...>{});
	return os << ")";
}

void integer_sequence_fun()
{
	std::cout << "print_sequence_fun" << std::endl;

	print_sequence(std::integer_sequence<unsigned, 9, 2, 5, 1, 9, 1, 6>{});
	print_sequence(std::make_integer_sequence<int, 20>{});
	print_sequence(std::make_index_sequence<10>{});
	print_sequence(std::index_sequence_for<float, std::iostream, char>{});

	std::array<int, 4> array = {1, 2, 3, 4};

	// 转换 array 为 tuple
	auto tuple = a2t(array);
	static_assert(std::is_same<decltype(tuple), std::tuple<int, int, int, int>>::value, "");

	// 打印到 cout
	std::cout << tuple << '\n';
}

void exchange_fun()
{
	std::cout << "exchange_fun" << std::endl;

	std::vector<int> vec1{1, 2};
	std::vector<int> vec2{3, 4};

	std::cout << "exchange before: " << std::endl;
	std::cout << "vec1: " << std::endl;
	std::copy(vec1.begin(), vec1.end(), std::ostream_iterator<int>{std::cout, " "});
	std::cout << std::endl;
	std::cout << "vec2: " << std::endl;
	std::copy(vec2.begin(), vec2.end(), std::ostream_iterator<int>{std::cout, " "});

	exchange(vec1, vec2);

	std::cout << std::endl;
	std::cout << "exchange after: " << std::endl;
	std::cout << "vec1: " << std::endl;
	copy(vec1.begin(), vec1.end(), std::ostream_iterator<int>{std::cout, " "});
	std::cout << std::endl;
	std::cout << "vec2: " << std::endl;
	copy(vec2.begin(), vec2.end(), std::ostream_iterator<int>{std::cout, " "});
	std::cout << std::endl;
}

void quoted_fun()
{
	std::cout << "quoted_fun" << std::endl;

	std::string str{"hello world"};
	std::cout << "origin Str:" << str << std::endl;				 // hello world
	std::cout << "quoted Str:" << std::quoted(str) << std::endl; // "hello world"
}

int main()
{
	make_unique_fun();
	threadSafe_fun();
	integer_sequence_fun();
	exchange_fun();
	quoted_fun();
	return 0;
}