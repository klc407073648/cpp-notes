#include <iostream>     // std::cout
#include <functional>   // std::bind

using namespace std;
// a function: (also works with function object: std::divides<double> my_divide;)
double my_divide (double x, double y) {return x/y;}

struct MyPair {
  double a,b;
  double multiply() {return a*b;}
};

struct MyAdd {
  double add(int a,int b) {return a+b;}
};

int main () {
  using namespace std::placeholders;    // adds visibility of _1, _2, _3,...

  // binding functions:
  auto fn_five = std::bind (my_divide,10,2);               // returns 10/2
  cout <<"fn_five(): "<<fn_five() << endl;                          	   // 5

  auto fn_half = std::bind (my_divide,_1,2);               // returns x/2
  cout <<"fn_half(10): "<< fn_half(10) << endl;                      		// 5

  auto fn_invert = std::bind (my_divide,_2,_1);            // returns y/x
  cout <<"fn_invert(10,2): "<< fn_invert(10,2) << endl;                      	// 0.2

  auto fn_rounding = std::bind<int> (my_divide,_1,_2);     // returns int(x/y)
  cout <<"fn_rounding(10,3): "<< fn_rounding(10,3) << endl;                   // 3

  MyPair ten_two {10,2};

  // binding members:
  auto bound_member_fn = std::bind (&MyPair::multiply,_1); // returns x.multiply()
  cout <<"bound_member_fn():ten_two.multiply() "<< bound_member_fn(ten_two) << endl;           // 20

  auto bound_member_data = std::bind (&MyPair::a,ten_two); // returns ten_two.a
  cout <<"bound_member_data():ten_two.a "<< bound_member_data() << endl;                // 10
  
  MyAdd mAdd;
    
  auto bound_member_fn_add = std::bind (&MyAdd::add,&mAdd,_1,_2); 	// returns mAdd.add(_1,_2)
  cout <<"bound_member_fn_add(30,50): "<< bound_member_fn_add(30,50) << endl;           		// 80

  return 0;
}