#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <tuple>
#include <algorithm>

using namespace std;

//g++ c11.cpp -o c11 -std=c++11
//g++ c11.cpp -o c11 -fno-elide-constructors -std=c++11
void testAuto()
{
    cout<<"testAuto:"<<endl;

    vector<int> vec={1,2,3,4,5};
    
    for(auto &i:vec){
        i++;
    }
    
    for(auto &i:vec){
        cout<<i<<" ";
    }
    cout<<endl;
}

class Student{
public:
    static int total;
    string name;
    int age;
    float scores;
};
int Student::total = 0;

void testDecltype()
{
    cout<<"testDecltype:"<<endl;

    int n = 0;
    const int &r = n;
    Student stu;
    decltype(n) a = n;  //n 为 int 类型，a 被推导为 int 类型
    decltype(r) b = n;     //r 为 const int& 类型, b 被推导为 const int& 类型
    decltype(Student::total) c = 0;  //total 为类 Student 的一个 int 类型的成员变量，c 被推导为 int 类型
    decltype(stu.name) url = "http://c.biancheng.net/cplus/";  //total 为类 Student 的一个 string 类型的成员变量， url 被推导为 string 类型

    cout<<"a:"<<a<<endl;
    cout<<"b:"<<b<<endl;
    cout<<"c:"<<c<<endl;
    cout<<"url:"<<url<<endl;
}

template <typename Val>
using str_map_t = std::map<std::string, Val>;

//可以统一处理以下场景
//typedef std::map<std::string, int> map_int_t;
//typedef std::map<std::string, std::string> map_str_t;

void testUsing()
{
    cout<<"testUsing:"<<endl;

    str_map_t<int> map1;
    str_map_t<std::string> map2;
    
    map1["age"]=27;
    map2["address"]="NJ";
    
    cout<<"map1[\"age\"]:"<<map1["age"]<<endl;
    cout<<"map2[\"address\"]:"<<map2["address"]<<endl;
}

template <typename R = int, typename T, typename U>
R func(T v1,U v2)
{
    return v1+v2;
}

void testFunTemplate()
{
    cout<<"testFunTemplate:"<<endl;

    auto r1=func(5.5,10);                    // R=int, T=double, U=int
    auto r2=func<double>(5.5,10);            // R=double, T=double, U=int
    auto r3=func<double, int, int>(5.5,10);  // R=double, T=int, U=int
    
    cout<<"r1:"<<r1<<endl;
    cout<<"r2:"<<r2<<endl;
    cout<<"r3:"<<r3<<endl;
}

void testTuple()
{
    cout<<"testTuple:"<<endl;

    std::tuple<int, char> first;                             // 1)   first{}
    std::tuple<int, char> second(first);                     // 2)   second{}
    std::tuple<int, char> third(std::make_pair(20, 'b'));   // 3)   third{20,'b'}
    std::tuple<long, char> fourth(third);                    // 4)的左值方式, fourth{20,'b'}
    std::tuple<int, char> fifth(10, 'a');                    // 5)的右值方式, fifth{10.'a'}
    std::tuple<int, char,string> sixth(std::make_tuple(30, 'c',"address"));    // 6)的右值方式, sixth{30, 'c',"address"}
    
    std::cout << std::get<0>(fourth) << " " << std::get<1>(fourth) << std::endl;
    std::cout << std::get<0>(fifth) << " " << std::get<1>(fifth) << std::endl;
    std::cout << std::get<0>(sixth) << " " << std::get<1>(sixth) << " " << std::get<2>(sixth) << std::endl;
    
    int size = std::tuple_size<decltype(sixth)>::value;
    std::cout << size << std::endl;
}

class Foo
{
public:
    Foo(int) {}
private:
    Foo(const Foo &);
};

void testInitList()
{
    cout<<"testInitList:"<<endl;

    Foo a1(123);
    //Foo a2 = 123;  //error: 'Foo::Foo(const Foo &)' is private
    Foo a3 = { 123 };
    Foo a4 { 123 };
    int a5 = { 3 };
    int a6 { 33 };
    
    cout<<"a5:"<<a5<<endl;
    cout<<"a6:"<<a6<<endl;
}

int all_num = 0;

void testLambda()
{
    cout<<"testLambda:"<<endl;

    int num[4] = {4, 2, 3, 1};
    //对 a 数组中的元素进行排序
    sort(num, num+4, [=](int x, int y) -> bool{ return x < y; } );
    for(int n : num){
        cout << n << " ";
    }
    cout<<endl;
    
    //display 即为 lambda 匿名函数的函数名
    auto display = [](int a,int b) -> void{cout << a << " " << b <<endl;};
    //调用 lambda 函数
    display(10,20);
    
    //抛出异常
    auto except = []()throw(int) {
        throw 10;
    };
    try {
        except();
    }
    catch (int) {
        cout << "捕获到了整形异常" <<endl;
    }
    
    //值传递和引用传递的区别
    //局部变量
    int num_1 = 1;
    int num_2 = 2;
    int num_3 = 3;
    cout << "lambda1:\n";
    auto lambda1 = [=]{
        //全局变量可以访问甚至修改
        all_num = 10;
        //函数体内只能使用外部变量，而无法对它们进行修改
        cout << num_1 << " "
             << num_2 << " "
             << num_3 << endl;
    };
    lambda1();
    cout << all_num <<endl;
    cout << "lambda2:\n";
    auto lambda2 = [&]{
        all_num = 100;
        num_1 = 10;
        num_2 = 20;
        num_3 = 30;
        cout << num_1 << " "
             << num_2 << " "
             << num_3 << endl;
    };
    lambda2();
    cout << all_num << endl;
}

void testForLoop()
{
    cout<<"testForLoop:"<<endl;

    char arc[] = "abcdefg";
    //for循环遍历普通数组
    for (char ch : arc) {
        cout << ch;
    }
    cout << endl;
    vector<char>myvector(arc, arc + 7);
    //for循环遍历 vector 容器
    for (auto ch : myvector) {
        cout << ch;
    }
    cout << endl;
}

void testConstexpr()
{
    cout<<"testConstexpr:"<<endl;

    constexpr int num = 1 + 2 + 3;
    int url[num] = {1,2,3,4,5,6};
    cout<< url[1] << endl;
}


//-fno-elide-constructions 关闭了g++编译器会省略函数返回值时临时对象的拷贝的优化。
class demo{
public:
    demo():num(new int(0)){
        cout<<"construct!"<<endl;
    }
    //拷贝构造函数
    demo(const demo &d):num(new int(*d.num)){
        cout<<"copy construct!"<<endl;
    }
    //移动构造函数
    demo(demo &&d):num(d.num){
        d.num = NULL;
        cout<<"move construct!"<<endl;
    }
    ~demo(){
      delete num;
      cout<<"class demo destruct!"<<endl;
   }
   
public:     //这里应该是 private，使用 public 是为了更方便说明问题
    int *num;
};

demo get_demo(){
    return demo();
}

void testMove()
{
    cout<<"testMove:"<<endl;

    demo demo1;
    cout << "demo2:"<< endl;//拷贝构造函数
    demo demo2 = demo1;
    cout << "demo3:"<< endl;
    demo demo3 = std::move(demo1);//移动构造函数
}


//重载被调用函数，查看完美转发的效果
void otherdef(int & t) {
    cout << "lvalue\n";
}
void otherdef(const int & t) {
    cout << "rvalue\n";
}
//实现完美转发的函数模板
template <typename T>
void function(T&& t) {
    otherdef(forward<T>(t));
}

void testForward()
{
    cout<<"testForward:"<<endl;

    string A("abc");
    string&& Rval = std::move(A);
    string B(Rval);    // this is a copy , not move.
    cout << A << endl;   // output "abc"
    string C(std::forward<string>(Rval));  // move.
    cout << A << endl;       /* output "" */
    
    function(5);
    int  x = 1;
    function(x);
}

void isnull(void *c){
    cout << "void*c" << endl;
}
void isnull(int n){
    cout << "int n" << endl;
}

void testNullptr()
{
    cout<<"testNullptr:"<<endl;

    isnull(0);
    //isnull(NULL);
    isnull(nullptr);
}

int main() 
{
    testAuto();
    testDecltype();
    testUsing();
    testFunTemplate();
    testTuple();
    testInitList();
    testLambda();
    testForLoop();
    testConstexpr();
    testMove();
    testForward();
    testNullptr();

    return 0;
}