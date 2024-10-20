//https://blog.csdn.net/zsiming/article/details/125542007


#include <iostream>
#include <memory>

using namespace std;

template<typename T>
class my_shared_ptr {
private:
	size_t* _useCnt;  
	T* _ptr;

public:
	// 默认构造函数
	my_shared_ptr() : _ptr(new T), _useCnt(new size_t(0)) {}

	// 构造函数
	explicit my_shared_ptr(T* p) : _ptr(p),  _useCnt(new size_t){
		if (p) {
			*_useCnt = 1;
		} else {
			*_useCnt = 0;
		}
	}

	// 拷贝构造函数
	my_shared_ptr(const my_shared_ptr& rhs) {
		_ptr = rhs._ptr; // 指向同一块内存
		_useCnt = rhs._useCnt;
		(*_useCnt)++; // 引用计数增加	
	}

	// 拷贝赋值函数，注意检查自赋值
	my_shared_ptr& operator= (const my_shared_ptr& rhs) {
		if (this != &rhs) {			// 检查自赋值
			if (_ptr) {				// 防止自身原来指向空指针，_useCnt>0说明确实是指向实体的
				--(*_useCnt);		// 自己要被rhs覆盖了，引用计数减1
				// 如果没有引用计数了，把自己清空，释放动态内存
				if (*_useCnt == 0) {
					delete _useCnt;
					delete _ptr;
				}
				// 把自己变成rhs, 引用计数加一
				_useCnt = rhs._useCnt;
				_ptr = rhs._ptr;
				++(*_useCnt);
			}
		}
		return *this;
	}


	// 得到计数
	int use_count() {
		return *_useCnt;
	}
	
	~my_shared_ptr() {
		if (!_ptr || (*_useCnt == 1)) { // 只有当前指针指向空或者只有一个指向对象时释放内存
			cout << "~my_shared_ptr():" <<*_ptr << endl;
			delete _useCnt;
			delete _ptr;
		} else {  // 否则只减少引用计数
			--(*_useCnt);
		}
	}
};


int main() {

	// 检查构造函数是否正常工作
	my_shared_ptr<int> p1(new int(1));
	cout << "p1 cnt:" << p1.use_count() << endl;

	// 检查拷贝构造是否正常工作
	{
		my_shared_ptr<int> p2(p1);
		cout << "p2 cnt:" << p2.use_count() << endl;
		cout << "p1 cnt:" << p1.use_count() << endl;
	}
	
	// 检查引用计数是否正常工作
	cout << "p1 cnt:" << p1.use_count() << endl;

	// 检查默认初始化时计数是否正常
	my_shared_ptr<int> p4;
	cout << "p4 cnt:" << p4.use_count() << endl;

	// 检查拷贝赋值是否正常工作
	p4 = p1;
	cout << "p1 cnt:" << p1.use_count() << " p4 cnt:" << p4.use_count() << endl;

	return 0;
}
