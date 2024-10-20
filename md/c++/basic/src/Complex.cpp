#include <iostream>
using namespace std;

class Complex {
  public:
    Complex(double real = 0.0, double imag = 0.0)
      : real_(real), imag_(imag) {}

    // 加法运算符重载
    Complex operator+(const Complex& other) const {
      return Complex(real_ + other.real_, imag_ + other.imag_);
    }

    // 输出运算符重载
    friend ostream& operator<<(ostream& os, const Complex& c) {
      os << c.real_ << " + " << c.imag_ << "i";
      return os;
    }

  private:
    double real_, imag_;
};

int main() {
  Complex c1(1, 2), c2(3, 4);
  Complex c3 = c1 + c2;
  cout << c3 << endl;
  return 0;
}