//#define BOOST_PYTHON_STATIC_LIB

#include<iostream>
#include<exception>
//#include "include/brigadier.hpp"
//#include "nbt/JsonToNBT.cpp"
//#include "brigadier/brigadier.h"
#include "MCjson.h"

using std::string;
using std::cout;
using std::endl;

class Test;
class Test2;
class Test3;
class Test4;
boost::python::object test();
string test2();

class Test {
public:
	virtual const void show() = 0;
	virtual ~Test() {};
	virtual Test* clone() = 0;
};

class Test2 : public Test {
private:
	int num;
public:
	Test2(const Test2& outher) { this->num = outher.num; }
	Test2(int i) { this->num = i; }
	void const show() { cout << this->num << endl; }
	~Test2() { cout << "~Test2" << endl; }
	Test* clone() { return new Test2(*this); }
};

typedef void (*Function)(int);
class Test3 {
private:
	Function func = 0;
public:
	Test3(void (*function)(int)) { this->func = function; };
	void do_func() { this->func(1); }
};

class Test4 {
private:
	static const Test3* func_class;
public:
	void call() { const_cast<Test3*>(this->func_class)->do_func(); }
};

const Test3* Test4::func_class = new Test3([](int input) {cout << "call_int: " << input << endl; });


boost::python::object test() {string s;
	JsonToNBT tools(new brigadier::StringReader(""));
	return tools.simple();
}

string test2() {
	return "";
}