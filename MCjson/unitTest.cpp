#include<iostream>
#include "include/brigadier.hpp"

using std::string;
using std::cout;
using std::endl;

class Test;
void test();
string test2();

class Test {
public:
	virtual const void show() = 0;
	virtual ~Test() {};
};

class Test2 : public Test {
private:
	int num;
public:
	Test2(int i) { this->num = i; }
	void const show() { cout << this->num << endl; }
	~Test2() { cout << "~Test2" << endl; }
};

void test() {
	Test* t = new Test2(1);
	t->show();
	delete t;
}

string test2() {
	return string();
}