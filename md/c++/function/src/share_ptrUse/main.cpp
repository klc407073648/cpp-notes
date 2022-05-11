#include <iostream>
#include <memory>

using namespace std;

class Test
{
public:
    Test(string s)
	:str(s)
    {
       cout<<"Test() create str: "<<str<<endl;
    }
    ~Test()
    {
        cout<<"~Test() delete str: "<<str<<endl;
    }
    string& getStr()
    {
        return str;
    }
    void setStr(const string& s)
    {
        str = s;
    }
    void print()
    {
        cout<<"str: "<<str<<endl;
    }
private:
    string str;
};

int main()
{
    shared_ptr<Test> ptest(new Test("123"));
    shared_ptr<Test> ptest2(new Test("456"));
	shared_ptr<Test> ptest3 = make_shared<Test>("789");
	
    cout<<"ptest2->getStr():"<<ptest2->getStr()<<endl;
    cout<<"ptest2.use_count():"<<ptest2.use_count()<<endl;
	
    ptest = ptest2;//“123”引用计数减1,计数为0自动销毁; "456"引用次数加1. (p=q的规则，p,q都为share_ptr)
    ptest->print();
	
    cout<<"ptest2.use_count():"<<ptest2.use_count()<<endl;//2
    cout<<"ptest.use_count():"<<ptest.use_count()<<endl;//2
	
	Test* mtest = ptest.get();
	mtest->print();
	
    ptest.reset();
    ptest2.reset();//此时“456”销毁
	
	cout<<"ptest3.unique():"<<boolalpha<<ptest3.unique()<<endl;
	shared_ptr<Test> ptest4(ptest3);
	cout<<"ptest3.unique():"<<boolalpha<<ptest3.unique()<<endl;
	ptest3.reset();
	ptest4.reset();
	
    cout<<"done !"<<endl;
    return 0;
}