#include <iostream>
#include <string>
using namespace std;

class MyString {
public:
    MyString() = default;
    MyString(const string& s) : str_(s) {
        cout << "Constructed: " << str_ << endl;
    }

    // 移动构造函数
    MyString(MyString&& other) noexcept {
        cout << "Moved: " << other.str_ << endl;
        str_ = move(other.str_);
    }

    // 移动赋值运算符
    MyString& operator=(MyString&& other) noexcept {
        cout << "Moved: " << other.str_ << endl;
        if (this != &other) {
            str_ = move(other.str_);
        }
        return *this;
    }

    ~MyString() {
        cout << "Destroyed: " << str_ << endl;
    }

private:
    string str_;
};

int main() {
    MyString a("Hello World");
    MyString b(move(a));
    MyString c;
    c = move(b);

    return 0;
}

/*
Constructed: Hello World
Moved: Hello World
Moved: Hello World
Destroyed: Hello World
Destroyed: 
Destroyed: 
*/