#ifndef _SINGLETONPTR_H_
#define _SINGLETONPTR_H_

#include <iostream>
#include <memory>

using namespace std;

/**
 * @brief 单例模式智能指针封装类
 * @details T 类型
 *          X 为了创造多个实例对应的Tag
 *          N 同一个Tag创造多个实例索引
 */
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


#endif //~_SINGLETONPTR_H_