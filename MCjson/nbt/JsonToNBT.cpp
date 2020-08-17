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

JsonToNBT::~JsonToNBT() {
	delete this->reader;
}

boost::python::object JsonToNBT::simple() {
	boost::python::list l_raw;
	l_raw.append("1");
	l_raw.append("2");
	boost::python::object l = l_raw;
	boost::python::dict res;
	res["data"] = l;
	return res;
}

boost::python::dict JsonToNBT::readSingleStruct() {
	boost::python::dict compoundnbt = this->readStruct();
	this->reader->skipWhitespace();
	if (this->reader->canRead()) {
		throw ERROR_TRAILING_DATA.createWithContext(this->reader);
	} else {
		return compoundnbt;
	}
}

boost::python::dict JsonToNBT::readStruct() {
	this->expect('{');
	boost::python::dict compoundnbt;
	this->reader->skipWhitespace();

	while (this->reader->canRead() && this->reader->peek() != '}')
	{
		int i = this->reader->getCursor();
		string s = this->readKey();
		if (s.empty()) {
			this->reader->setCursor(i);
			throw ERROR_EXPECTED_KEY.createWithContext(this->reader);
		}

		this->expect(':');
		compoundnbt[s] = this->readValue();
		if (!this->hasElementSeparator()) {
			break;
		}
		
		if (!this->reader->canRead()) {
			throw ERROR_EXPECTED_KEY.createWithContext(this->reader);
		}
	}

	this->expect('}');
	return compoundnbt;
}

void JsonToNBT::expect(char expected) {
	this->reader->skipWhitespace();
	this->reader->expect(expected);
}