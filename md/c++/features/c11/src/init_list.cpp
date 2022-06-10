class Foo
{
public:
    Foo(int) {}
private:
    Foo(const Foo &);
};
int main(void)
{
    Foo a1(123);
    Foo a2 = 123;  //error: 'Foo::Foo(const Foo &)' is private
    Foo a3 = { 123 };
    Foo a4 { 123 };
    int a5 = { 3 };
    int a6 { 3 };
    return 0;
}