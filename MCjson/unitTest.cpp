#include<iostream>

using std::string;
using std::cout;
using std::endl;

class Test;
void test();
string test2();

class Test {
public:
	virtual void show() = 0;
};

class Test2 : public Test {
private:
	int num;
public:
	Test2(int i) { this->num = i; }
	void show() { cout << this->num << endl; }
};

void test() {
	string a;
	int leng = (int)a.length();
	cout << leng << endl;
	a.append("wwwww");
	leng = (int)a.length();
	cout << leng << endl;
	string b = test2();
	cout << b.length() << endl;
}

string test2() {
	return string();
}