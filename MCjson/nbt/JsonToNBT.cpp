#include "nbt.h"

using std::string;
using namespace brigadier;

const SimpleCommandExceptionType JsonToNBT::ERROR_TRAILING_DATA = SimpleCommandExceptionType(new LiteralMessage("ERROR_TRAILING_DATA"));
const SimpleCommandExceptionType JsonToNBT::ERROR_EXPECTED_KEY  = SimpleCommandExceptionType(new LiteralMessage("ERROR_EXPECTED_KEY"));
const SimpleCommandExceptionType JsonToNBT::ERROR_EXPECTED_VALUE = SimpleCommandExceptionType(new LiteralMessage("ERROR_EXPECTED_VALUE"));
const Dynamic2CommandExceptionType JsonToNBT::ERROR_INSERT_MIXED_LIST = Dynamic2CommandExceptionType([](const string& var1, const string& var2)->Message* {
	return new LiteralMessage("ERROR_INSERT_MIXED_LIST " + var1 + ", found " + var2);
	});
const Dynamic2CommandExceptionType JsonToNBT::ERROR_INSERT_MIXED_ARRAY = Dynamic2CommandExceptionType([](const string& var1, const string& var2)->Message* {
	return new LiteralMessage("ERROR_INSERT_MIXED_ARRAY " + var1 + ", found " + var2);
	});
const DynamicCommandExceptionType JsonToNBT::ERROR_INVALID_ARRAY = DynamicCommandExceptionType([](const string& expected)->Message* {
	return new LiteralMessage("Expected literal " + expected);
	});

const boost::RegEx JsonToNBT::DOUBLE_PATTERN_NOSUFFIX = boost::RegEx("[-+]?(?:[0-9]+[.]|[0-9]*[.][0-9]+)(?:e[-+]?[0-9]+)?");
const boost::RegEx JsonToNBT::DOUBLE_PATTERN = boost::RegEx("[-+]?(?:[0-9]+[.]?|[0-9]*[.][0-9]+)(?:e[-+]?[0-9]+)?d");
const boost::RegEx JsonToNBT::FLOAT_PATTERN = boost::RegEx("[-+]?(?:[0-9]+[.]?|[0-9]*[.][0-9]+)(?:e[-+]?[0-9]+)?f");
const boost::RegEx JsonToNBT::BYTE_PATTERN = boost::RegEx("[-+]?(?:0|[1-9][0-9]*)b");
const boost::RegEx JsonToNBT::LONG_PATTERN = boost::RegEx("[-+]?(?:0|[1-9][0-9]*)l");
const boost::RegEx JsonToNBT::SHORT_PATTERN = boost::RegEx("[-+]?(?:0|[1-9][0-9]*)s");
const boost::RegEx JsonToNBT::INT_PATTERN = boost::RegEx("[-+]?(?:0|[1-9][0-9]*)");

JsonToNBT::JsonToNBT() {};

JsonToNBT::JsonToNBT(StringReader* r) : reader(r) {};

boost::python::object JsonToNBT::simple() {
	boost::python::list l_raw;
	l_raw.append("1");
	l_raw.append("2");
	boost::python::object l = l_raw;
	boost::python::dict res;
	res["data"] = l;
	return res;
}