#include "Singleton.h"

Singleton::Ptr Singleton::m_instance_ptr = nullptr;
std::mutex Singleton::m_mutex;//静态变量不写默认为NULL

Singleton::Singleton()
{
  cout<<"Singleton()"<<endl;
}

Singleton::~Singleton()
{
  cout<<"~Singleton()"<<endl;
}
    
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
