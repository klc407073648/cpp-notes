#include <iostream>

// 形状类
class Shape
{
public:
  virtual double calcArea()
  {
    std::cout << "Shape::calcArea" << std::endl;
  }
  Shape() { std::cout << "Shape::Shape" << std::endl; }
  virtual ~Shape() { std::cout << "Shape::~Shape" << std::endl; }
};

// 圆形类
class Circle : public Shape
{
public:
  Circle(double r) : _r(r)
  {
    std::cout << "Circle::Circle" << std::endl;
  }
  ~Circle()
  {
    std::cout << "Circle::~Circle" << std::endl;
  }
  virtual double calcArea()
  {
    std::cout << "Circle::calcArea:" << 3.14 * _r * _r << std::endl;
  }

private:
  double _r;
};

int main()
{
  Shape *shape1 = new Circle(4.0);
  shape1->calcArea();
  delete shape1; // 因为Shape有虚析构函数，所以delete释放内存时，先调用子类析构函数，再调用基类析构函数，防止内存泄漏。
  shape1 = nullptr;
  return 0;
}