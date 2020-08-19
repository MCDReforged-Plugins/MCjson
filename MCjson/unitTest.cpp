//#define BOOST_PYTHON_STATIC_LIB

#include<iostream>
#include<exception>
//#include "include/brigadier.hpp"
//#include "nbt/JsonToNBT.cpp"
//#include "brigadier/brigadier.h"
#include "MCjson.h"
#include <boost/foreach.hpp>

using std::string;
using std::cout;
using std::endl;

class str;
class Test;
class Test2;
class Test3;
class Test4;
boost::python::object test();
void test2();
template<class T>
void pure_cout(T s);

class str {
private:
	string s;
public:
	str(string s): s(s) {}
	void show() { cout << this->s << endl; }
};

class Test {
public:
	virtual const void show() {};
	virtual ~Test() {};
	virtual Test* clone() { return 0; };
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


boost::python::object test() {
	Test t1;
	Test2 t2(1);
	Test t3 = Test2(2);
	t1.show();
	t2.show();
	t3.show();
	return boost::python::dict();
}

void test2() {
	for (int count = 1; count <= 10000; count++) {
		brigadier::StringReader* reader = new brigadier::StringReader("xxx");
		reader->setCursor(2);
		try {
			brigadier::LiteralMessage* message = new brigadier::LiteralMessage("ERROR_TRAILING_DATA");
			brigadier::SimpleCommandExceptionType exception_type(message);
			brigadier::CommandSyntaxException exception = exception_type.createWithContext(reader);
			throw exception;
		}
		catch (brigadier::Exception& e) {
			cout << e.getMessage() << endl;
		}
		delete(reader);
	}
}

template<class T>
void pure_cout(T s) {
	cout << "[C output] " << s << endl;;
}

int main() {

	test2();

	cout << "ok" << endl;
	return 0;
}