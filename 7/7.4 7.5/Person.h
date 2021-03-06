#pragma once
//#ifndef PERSON_H
//#define PERSON_H
#include <string>
class Person
{
public:
	std::string name;
	std::string address;
	//获取name和address的成员函数应该是const的，因为这些成员函数不会修改对象。（而且const的成员函数能够对const Person类型使用更泛用）
	std::string get_name() const { return name; }
	std::string get_address() const { return address; }
private:

};

//#endif