#define BOOST_PYTHON_STATIC_LIB

#ifndef _DEBUG
#include <boost/python.hpp>
#include<iostream>

boost::python::object test(boost::python::str);

BOOST_PYTHON_MODULE(MCjson) {
	using namespace boost::python;
	scope().attr("version") = "0.1";
	def("t", &test);
}

#endif