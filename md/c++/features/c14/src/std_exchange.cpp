#include <utility>

template <class T, class U = T>
T exchange(T &obj, U &&new_value)
{
  T old_value = std::move(obj);
  obj = std::forward<U>(new_value);
  return old_value;
}