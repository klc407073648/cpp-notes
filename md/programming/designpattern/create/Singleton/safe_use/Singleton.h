#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <iostream>
#include <memory>
#include <mutex> 

using namespace std;

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


#endif //~_SINGLETON_H_