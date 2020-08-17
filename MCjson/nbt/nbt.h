//#pragma once

#define BOOST_PYTHON_STATIC_LIB

#include <string>
#include <boost/regex.h>
#include <boost/python.hpp>

#include "../brigadier/brigadier.h"

class JsonToNBT {
private:
	brigadier::StringReader* reader = 0;
	bool hasElementSeparator();
protected:
	string readKey();
	boost::python::object readTypedValue();
	boost::python::object type(string stringIn);
	boost::python::object readValue();
	boost::python::object readList();
public:
	static const brigadier::SimpleCommandExceptionType ERROR_TRAILING_DATA;
	static const brigadier::SimpleCommandExceptionType ERROR_EXPECTED_KEY;
	static const brigadier::SimpleCommandExceptionType ERROR_EXPECTED_VALUE;
	static const brigadier::Dynamic2CommandExceptionType ERROR_INSERT_MIXED_LIST;
	static const brigadier::Dynamic2CommandExceptionType ERROR_INSERT_MIXED_ARRAY;
	static const brigadier::DynamicCommandExceptionType ERROR_INVALID_ARRAY;

	static const boost::RegEx DOUBLE_PATTERN_NOSUFFIX;
	static const boost::RegEx DOUBLE_PATTERN;
	static const boost::RegEx FLOAT_PATTERN;
	static const boost::RegEx BYTE_PATTERN;
	static const boost::RegEx LONG_PATTERN;
	static const boost::RegEx SHORT_PATTERN;
	static const boost::RegEx INT_PATTERN;

	JsonToNBT();
	JsonToNBT(brigadier::StringReader*);
	~JsonToNBT();
	boost::python::object simple();
	boost::python::dict readSingleStruct();
	boost::python::dict readStruct();
	void expect(char expected);
};