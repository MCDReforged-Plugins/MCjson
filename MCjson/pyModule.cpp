#define BOOST_PYTHON_STATIC_LIB

#include <boost/python.hpp>

BOOST_PYTHON_MODULE(MCjson) {
	using namespace boost::python;
	scope().attr("version") = "0.1";
}