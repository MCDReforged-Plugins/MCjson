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

boost::RegEx JsonToNBT::DOUBLE_PATTERN_NOSUFFIX = boost::RegEx("[-+]?(?:[0-9]+[.]|[0-9]*[.][0-9]+)(?:e[-+]?[0-9]+)?");
boost::RegEx JsonToNBT::DOUBLE_PATTERN = boost::RegEx("[-+]?(?:[0-9]+[.]?|[0-9]*[.][0-9]+)(?:e[-+]?[0-9]+)?d");
boost::RegEx JsonToNBT::FLOAT_PATTERN = boost::RegEx("[-+]?(?:[0-9]+[.]?|[0-9]*[.][0-9]+)(?:e[-+]?[0-9]+)?f");
boost::RegEx JsonToNBT::BYTE_PATTERN = boost::RegEx("[-+]?(?:0|[1-9][0-9]*)b");
boost::RegEx JsonToNBT::LONG_PATTERN = boost::RegEx("[-+]?(?:0|[1-9][0-9]*)l");
boost::RegEx JsonToNBT::SHORT_PATTERN = boost::RegEx("[-+]?(?:0|[1-9][0-9]*)s");
boost::RegEx JsonToNBT::INT_PATTERN = boost::RegEx("[-+]?(?:0|[1-9][0-9]*)");

JsonToNBT::JsonToNBT() {};

JsonToNBT::JsonToNBT(StringReader* r) : reader(r) {};

JsonToNBT::~JsonToNBT() {
	delete this->reader;
}

bool JsonToNBT::hasElementSeparator() {
	this->reader->skipWhitespace();
	if (this->reader->canRead() && this->reader->peek() == ',') {
		this->reader->skip();
		this->reader->skipWhitespace();
		return true;
	} else {
		return false;
	}
}

string JsonToNBT::readKey() {
	this->reader->skipWhitespace();
	if (!this->reader->canRead()) {
		throw ERROR_EXPECTED_KEY.createWithContext(this->reader);
	} else {
		return this->reader->readString();
	}
}

boost::python::object JsonToNBT::readTypedValue() {
	this->reader->skipWhitespace();
	int i = this->reader->getCursor();
	if (StringReader::isQuotedStringStart(this->reader->peek())) {
		return boost::python::str(this->reader->readQuotedString());  //StringNBT
	} else {
		string s = this->reader->readUnquotedString();
		if (s.empty()) {
			this->reader->setCursor(i);
			throw ERROR_EXPECTED_VALUE.createWithContext(this->reader);
		} else {
			return this->type(s);
		}
	}
}

boost::python::object JsonToNBT::type(string stringIn) {
	try {
		if (FLOAT_PATTERN.Match(stringIn)) {
			return boost::python::make_tuple(std::stof(stringIn.substr(0, stringIn.length())))[0];  //FloatNBT
		}
		if (BYTE_PATTERN.Match(stringIn)) {
			return boost::python::str(stringIn.substr(0, stringIn.length()));  //ByteNBT -> Str
		}
		if (LONG_PATTERN.Match(stringIn)) {
			return boost::python::make_tuple(std::stol(stringIn.substr(0, stringIn.length())))[0];  //LongNBT
		}
		if (SHORT_PATTERN.Match(stringIn)) {
			return boost::python::make_tuple(std::stoi(stringIn.substr(0, stringIn.length())))[0];  //ShortNBT -> Int
		}
		if (INT_PATTERN.Match(stringIn)) {
			return boost::python::long_(std::stoi(stringIn));  //IntNBT
		}
		if (DOUBLE_PATTERN.Match(stringIn)) {
			return boost::python::make_tuple(std::stod(stringIn.substr(0, stringIn.length())))[0];  //DoubleNBT
		}
		if (DOUBLE_PATTERN_NOSUFFIX.Match(stringIn)) {
			return boost::python::make_tuple(std::stod(stringIn))[0];  //DoubleNBT
		}
		if ("true" == stringIn) {
			return boost::python::long_(1);  //ByteNBT(bool) -> Int
		}
		if ("false" == stringIn) {
			return boost::python::long_(0);  //ByteNBT(bool) -> Int
		}
	} catch (std::invalid_argument) {
		;
	}

	return boost::python::str(stringIn);
}

boost::python::object JsonToNBT::readValue() {
	this->reader->skipWhitespace();
	if (!this->reader->canRead()) {
		throw ERROR_EXPECTED_VALUE.createWithContext(this->reader);
	} else {
		char c0 = this->reader->peek();
		if (c0 == '{') {
			return this->readStruct();
		} else {
			return (c0 == '[') ? this->readList() : this->readTypedValue();
		}
	}
}

boost::python::object JsonToNBT::readList() {
	return (this->reader->canRead(3) && !StringReader::isQuotedStringStart(this->reader->peek(1)) && this->reader->peek(2) == ';') ? this->readArrayTag() : this->readListTag();
}

boost::python::object JsonToNBT::readListTag() {
	this->expect('[');
	this->reader->skipWhitespace();
	if (!this->reader->canRead()) {
		throw ERROR_EXPECTED_VALUE.createWithContext(this->reader);
	} else {
		boost::python::list listnbt;
		int i = -1;

		while (this->reader->peek() != ']') {
			int j = this->reader->getCursor();
			boost::python::object inbt = this->readValue();
			//Still at here
			
		}

		this->expect(']');
		return listnbt;
	}
}

boost::python::object JsonToNBT::readArrayTag() {
	return boost::python::object();
}

boost::python::object JsonToNBT::readArray(char a, char b) {
	return boost::python::object();
}

boost::python::object JsonToNBT::simple() {
	boost::python::list l_raw;
	l_raw.append("1");
	l_raw.append("2");
	boost::python::object l = l_raw;
	boost::python::dict res;
	res["data"] = l;
	res["num"] = boost::python::make_tuple(std::stod("1.555332445"));
	res["num_cource"] = 1.555332445;
	res["str_data"] = string("string_data");
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