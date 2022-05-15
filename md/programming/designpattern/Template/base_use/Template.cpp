#include "Template.h"
#include <iostream>
using namespace std;

TemplateBase::TemplateBase()
{
}

TemplateBase::~TemplateBase()
{

}

void TemplateBase::TemplateMethod()
{
	this->Operation1();
	this->Operation2();
}

Template1::Template1()
{

}

Template1::~Template1()
{

}

void Template1::Operation1()
{
	cout<<"Template1...Operation1"<<endl;
}

void Template1::Operation2()
{
	cout<<"Template1...Operation2"<<endl;
}

Template2::Template2()
{

}

Template2::~Template2()
{

}

void Template2::Operation1()
{
	cout<<"Template2...Operation1"<<endl;
}

void Template2::Operation2()
{
	cout<<"Template2...Operation2"<<endl;
}