//#pragma once

#define BOOST_PYTHON_STATIC_LIB

#include <string>
#include <boost/regex.h>
#include <boost/python.hpp>

#include "../brigadier/brigadier.h"

class JsonToNBT {
private:
	brigadier::StringReader* reader = 0;
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
	boost::python::object simple();
};

class INBT {
public:
	std::string NBT_TYPES[13] = { "END", "BYTE", "SHORT", "INT", "LONG", "FLOAT", "DOUBLE", "BYTE[]", "STRING", "LIST", "COMPOUND", "INT[]", "LONG[]" };
	virtual std::string toString() = 0;
	virtual char getId() = 0;
	virtual INBT* copy() = 0;
	std::string getString();
};

class NBTBuilder {
public:
	static INBT* create(char id);
	static std::string getTypeName(char id);
};

class EndNBT : public INBT {
public:
	std::string toString() override;
	char getId() override;
	INBT* copy() override;
	char hashCode();
};