#include <iostream>
#include <cstring>
using namespace std;
//Person类
class Person
{
public:
    Person(string name, int age):m_name(name),m_age(age)
    {
	}
	virtual void info()
	{
		cout << "Person info, Name = " << this->m_name << " Age = " << this->m_age << endl;
	}
protected:
    string m_name;
    int m_age;
};
class Student:public Person
{
public:
    Student(string name, int age, float score):Person(name, age),m_score(score)
    {
	}
	virtual void info()
	{
		cout << "Student info, Name = " << this->m_name << " Age = " << this->m_age << " Score = " << m_score << endl;
	}
protected:
    float m_score;
};

int main()
{
	Person person("Jason", 18);
	Student student("Tom", 20, 100);
	Person &rPerson = person;
    Person &rStudent = student;
    rPerson.info();
    rStudent.info();
	return 0;
}