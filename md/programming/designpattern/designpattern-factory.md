# 设计模式

​[[toc]]

> 工厂模式(Factory): 定义一个用以创建对象的接口, 让子类决定实例化哪个类. 当遇到需要根据某个前提条件创建不同的类实现时, 会实用工厂模式.。

Factory基类中定义创建Prodcut的接口（virtual Product *CreateProduct() = 0;），由子类ConcreteFactory去实现具体的创建过程。

```cpp
class Factory
{
	public:
		virtual ~Factory() = 0;
		virtual Product *CreateProduct() = 0;

	protected:
		Factory();

	private:
};

class ConcreteFactory : public Factory
{
	public:
		~ConcreteFactory();
		ConcreteFactory();
		Product *CreateProduct();

	protected:
	private:
};

Product *ConcreteFactory::CreateProduct()
{
	return new ConcreteProduct();
}
—————————————————————————————————————————————————————————————
class Product
{
	public:
		virtual ~Product() = 0;

	protected:
		Product();

	private:
};

class ConcreteProduct : public Product
{
	public:
		~ConcreteProduct();
		ConcreteProduct();

	protected:
	private:
};
```

使用方法：

```cpp
	Factory* fac = new ConcreteFactory();
	Product* p = fac->CreateProduct();
	
	delete p;
	delete fac;
```

执行结果如下：

```cpp
[root@192 safe_use]# ./Factory
Factory.....
ConcreteFactory.....
Product....
ConcreteProduct....
~ConcreteProduct....
~Product....
~ConcreteFactory.....
~Factory.....
```
​