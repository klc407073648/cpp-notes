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
    otherdef(std::forward<T>(t));
}

void testForward(){
    string A("abc");
    string&& Rval = std::move(A);
    string B(Rval);    // this is a copy , not move.
    cout << A << endl;   // output "abc"
    string C(std::forward<string>(Rval));  // move.
    cout << A << endl;       /* output "" */
    
    function(5);  //rvalue
    int  x = 1;
    function(x);  //lvalue
}