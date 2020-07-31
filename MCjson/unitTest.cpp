#include<iostream>
#include<exception>
#include "include/brigadier.hpp"

using std::string;
using std::cout;
using std::endl;

class Test;
class Test2;
class Test3;
void test();
Test* test2();

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

class Test3 {
private:
	void (* func)(int);
public:
	Test3(void (*function)(int)) { this->func = function; };
	void do_func() { this->func(1); }
};




void test() {
	auto f = [](int input) {cout << "call_int: " << input << endl; };
	Test3 o(f);
	o.do_func();
}

Test* test2() {
	
}