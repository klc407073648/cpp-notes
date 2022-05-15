# 单例模式

​[[toc]]

> 单例模式(Singleton): 保证一个类仅有一个实例,并提供一个访问它的全局控制点. 比如在加载配置文件时, 可使用该模式。

最基础的实现：

注意单例模式从概念上就是维持一个唯一的实例对象，但是该对象不能直接创建，只能通过静态方法getInstance实现。同时，构造函数要声明为protected 或 private，避免被显示调用。

```cpp
class Singleton
{
	public:
		static Singleton* getInstance();
		//~Singleton();
	protected:
		Singleton();//Singleton 不能被实例化，因此将构造函数声明为protected 或 private
		
	private:
		static Singleton* _instance;
};


Singleton* Singleton::getInstance()
{
	if (_instance == 0)
	{
		_instance = new Singleton();
	}
	
	return _instance;
}
```

调用方法：

```cpp
Singleton* sgn = Singleton::getInstance();
```

考虑到线程安全和内存泄漏，进一步改进：

1. 单例模式对象是禁止拷贝构造和赋值的

2. 利用智能指针shared_ptr来自动释放申请的内存

3. 为了避免多个线程同时调用getInstance函数引起错误，加入互斥锁，确保仅创建一个实例。

```cpp
class Singleton{
public:
    typedef std::shared_ptr<Singleton> Ptr;
    
    Singleton(Singleton&)=delete;//禁止拷贝构造
    Singleton& operator=(const Singleton&)=delete;//禁止赋值
    static Ptr getInstance();
	~Singleton();
	
private:
    Singleton();
	
private:
    static Ptr m_instance_ptr;
    static std::mutex m_mutex;
};
 
Singleton::Ptr Singleton::getInstance()
{
    if(m_instance_ptr==nullptr)
	{
        std::lock_guard<std::mutex> lk(m_mutex);   
	    if(m_instance_ptr == nullptr)
		 {
             m_instance_ptr = std::shared_ptr<Singleton>(new Singleton);
         }
    }
	
    return m_instance_ptr;
}
```

调用方法：

```cpp
	Singleton::Ptr m_singleton = Singleton::getInstance();
```

考虑封装单例智能指针类，通过typedef SingletonPtr<worker> workerPtr;定义一个指向特定对象worker的智能指针workerPtr，然后调用getInstance获取指针对象，进一步调用成员函数myWorkFun：

```cpp
template<class T, class X = void, int N = 0>
class SingletonPtr 
{
	public:
		/**
		 * @brief 返回单例智能指针
		 */
		static std::shared_ptr<T> getInstance()
		{
			static std::shared_ptr<T> v(new T);
			return v;
        }
};

class worker 
{
	public:
		worker()
		{
			cout<<"worker()"<<endl;
		}
		~worker()
		{
			cout<<"~worker()"<<endl;
		}
		
		void myWorkFun()
		{
			cout<<"I'm working"<<endl;
		}
};


typedef SingletonPtr<worker> workerPtr;

调用方法：
workerPtr::getInstance()->myWorkFun();
```
	
执行结果：

```bash
[root@192 share_ptr_use]# ./Singleton
worker()
I'm working
~worker()
```

​