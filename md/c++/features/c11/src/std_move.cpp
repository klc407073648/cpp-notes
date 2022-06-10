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
    demo demo1;
    cout << "demo2:"<< endl;//拷贝构造函数
    demo demo2 = demo1;
    cout << "demo3:"<< endl;
    demo demo3 = std::move(demo1);//移动构造函数
}