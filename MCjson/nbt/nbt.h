//#pragma once

#define BOOST_PYTHON_STATIC_LIB

#include <string>
#include <boost/regex.h>
#include <boost/python.hpp>

#include "../brigadier/brigadier.h"

/*
class INBT {
public:
	static const std::string NBT_TYPES[];
	//virtual std::string toString() = 0;
	//virtual std::string getString();
	virtual short getId() const = 0;
	virtual INBT* copy() const = 0;
	virtual boost::python::object extractPyObject() const = 0;
	virtual ~INBT();
};

class NBTBuilder {
public:
	static INBT* create(short id);
	static std::string getTypeName(short id);
};

class EndNBT : public INBT {
public:
	short getId() const override;
	INBT* copy() const override;
	boost::python::object extractPyObject() const override;
	bool equals(INBT* ptr) const;  //Not used in other classes
};

class ByteNBT : public INBT {
private:
	char data;
public:
	short getId() const override;
	INBT* copy() const override;
	boost::python::object extractPyObject() const override;
};

class ShortNBT : public INBT {
public:
	short getId() const override;
	INBT* copy() const override;
	boost::python::object extractPyObject() const override;
};

class IntNBT : public INBT {
public:
	short getId() const override;
	INBT* copy() const override;
	boost::python::object extractPyObject() const override;
};

class LongNBT : public INBT {
public:
	short getId() const override;
	INBT* copy() const override;
	boost::python::object extractPyObject() const override;
};

class FloatNBT : public INBT {
public:
	short getId() const override;
	INBT* copy() const override;
	boost::python::object extractPyObject() const override;
};

class DoubleNBT : public INBT {
public:
	short getId() const override;
	INBT* copy() const override;
	boost::python::object extractPyObject() const override;
};

class ByteArrayNBT : public INBT {
public:
	short getId() const override;
	INBT* copy() const override;
	boost::python::object extractPyObject() const override;
};

class StringNBT : public INBT {
public:
	short getId() const override;
	INBT* copy() const override;
	boost::python::object extractPyObject() const override;
};

class ListNBT : public INBT {
public:
	short getId() const override;
	INBT* copy() const override;
	boost::python::object extractPyObject() const override;
};

class CompoundNBT : public INBT {  //Unuse: using boost::python::dict
public:
	short getId() const override;
	INBT* copy() const override;
	boost::python::object extractPyObject() const override;
};

class IntArrayNBT : public INBT {
public:
	short getId() const override;
	INBT* copy() const override;
	boost::python::object extractPyObject() const override;
};

class LongArrayNBT : public INBT {
public:
	short getId() const override;
	INBT* copy() const override;
	boost::python::object extractPyObject() const override;
};
*/

class JsonToNBT {
private:
	static boost::RegEx DOUBLE_PATTERN_NOSUFFIX;
	static boost::RegEx DOUBLE_PATTERN;
	static boost::RegEx FLOAT_PATTERN;
	static boost::RegEx BYTE_PATTERN;
	static boost::RegEx LONG_PATTERN;
	static boost::RegEx SHORT_PATTERN;
	static boost::RegEx INT_PATTERN;
	
	brigadier::StringReader* reader = 0;
	bool hasElementSeparator();
	boost::python::object type(std::string stringIn);
	boost::python::object readListTag();
	boost::python::object readArrayTag();
	boost::python::object readArray(short a, short b);
	void expect(char expected);
protected:
	std::string readKey();
	boost::python::object readTypedValue();
	boost::python::object readValue();
	boost::python::object readList();
public:
	static const brigadier::SimpleCommandExceptionType ERROR_TRAILING_DATA;
	static const brigadier::SimpleCommandExceptionType ERROR_EXPECTED_KEY;
	static const brigadier::SimpleCommandExceptionType ERROR_EXPECTED_VALUE;
	static const brigadier::Dynamic2CommandExceptionType ERROR_INSERT_MIXED_LIST;
	static const brigadier::Dynamic2CommandExceptionType ERROR_INSERT_MIXED_ARRAY;
	static const brigadier::DynamicCommandExceptionType ERROR_INVALID_ARRAY;

	JsonToNBT();
	JsonToNBT(brigadier::StringReader*);
	~JsonToNBT();
	boost::python::dict readSingleStruct();
	boost::python::dict readStruct();
};