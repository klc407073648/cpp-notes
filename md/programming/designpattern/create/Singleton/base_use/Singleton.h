#ifndef _SINGLETON_H_
#define _SINGLETON_H_
#include <iostream>

using namespace std;

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
#endif //~_SINGLETON_H_