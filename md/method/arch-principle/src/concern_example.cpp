template <typename T>
void bulb_sort(T objects[], size_t num_of_objects)
{
  for (size_t y = 0; y < num_of_objects - 1; y++)
  {
    for (size_t x = 1; x < num_of_objects - y; x++)
    {
      if (objects[x] > objects[x - 1])
        SWAP(objects[x], objects[x - 1]);
    }
  }
}
struct Student
{
  bool operator>(const Student &another) const { return height > another.height; }

private:
  char name[MAX_NAME_LEN];
  unsigned int height;
};

template <typenameT>
void qsort(T objects[], size_t num_of_objects)
{
  //快速排序的实现
  if (objects[i] > objects[i + 1])
}

template <typename T, typename GreaterThan>
void bulb_sort(T objects[], size_t num_of_objects, const GreaterThan &greater than)

for (size_ty = 0; y < num_of_objects - 1; y++)
{
  for (size_tx = 1; x < num_of_objects - y; x++)
  {
    if (greater_than(objects[x], objects[x - 1]))
    {
      SWAP(objects[x], objects[x - 1]);
    }
  }
}

struct Student
{
  char name[MAX_NAME_LEN];
  unsigned int age;
  unsigned int height;
};

bool student_older_than(const Student &Ihs, const Student &rhs)
{
  return Ihs.age > rhs.age;
}
bool student_taller_than(const Student &Ihs, const Student &rhs)
{
  return Ihs.height > rhs.height;
}

template <typename T>
struct GreaterThan
{
  bool operator()(const T &Ihs, const T &rhs) const { return Ihs > rhs; }
};

template <typename T>
void bulb_sort(T objects[] size_t num_of_objects)
{
  bulb_sort(objects, num_of_objects, GreaterThan<T>());
}
