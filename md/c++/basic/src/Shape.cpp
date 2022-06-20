#include <iostream>

// 形状类
class Shape
{
public:
  virtual double calcArea()
  {
    std::cout << "Shape::calcArea" << std::endl;
  }
  virtual ~Shape() {}
};

// 圆形类
class Circle : public Shape
{
public:
  Circle(double r) : _r(r)
  {
  }
  ~Circle()
  {
  }
  virtual double calcArea()
  {
    std::cout << "Circle::calcArea:" << 3.14 * _r * _r << std::endl;
  }

private:
  double _r;
};

// 矩形类
class Rectangle : public Shape
{
public:
  Rectangle(double x, double y) : _x(x), _y(y)
  {
  }
  ~Rectangle()
  {
  }
  virtual double calcArea()
  {
    std::cout << "Rectangle::calcArea:" << _x * _y << std::endl;
  }

private:
  double _x;
  double _y;
};

int main()
{
  Shape *shape1 = new Circle(4.0);         // Circle::calcArea:50.24
  Shape *shape2 = new Rectangle(5.0, 6.0); // Rectangle::calcArea30
  shape1->calcArea();                      // 调用圆形类里面的方法
  shape2->calcArea();                      // 调用矩形类里面的方法
  delete shape1;
  shape1 = nullptr;
  delete shape2;
  shape2 = nullptr;
  return 0;
}