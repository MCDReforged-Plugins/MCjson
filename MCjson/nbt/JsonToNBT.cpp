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
			return boost::python::make_tuple(std::stof(stringIn.substr(0, stringIn.length() - 1)))[0];  //FloatNBT
		}
		if (BYTE_PATTERN.Match(stringIn)) {
			return boost::python::long_(stringIn.substr(0, stringIn.length() - 1));  //ByteNBT -> Int
		}
		if (LONG_PATTERN.Match(stringIn)) {
			return boost::python::make_tuple(std::stol(stringIn.substr(0, stringIn.length() - 1)))[0];  //LongNBT
		}
		if (SHORT_PATTERN.Match(stringIn)) {
			return boost::python::long_(std::stoi(stringIn.substr(0, stringIn.length() - 1)));  //ShortNBT -> Int
		}
		if (INT_PATTERN.Match(stringIn)) {
			return boost::python::long_(std::stoi(stringIn));  //IntNBT
		}
		if (DOUBLE_PATTERN.Match(stringIn)) {
			return boost::python::make_tuple(std::stod(stringIn.substr(0, stringIn.length() - 1)))[0];  //DoubleNBT
		}
		if (DOUBLE_PATTERN_NOSUFFIX.Match(stringIn)) {
			return boost::python::make_tuple(std::stod(stringIn))[0];  //DoubleNBT
		}
		if ("true" == stringIn) {
			return boost::python::object(true);  //ByteNBT(bool) -> Bool
		}
		if ("false" == stringIn) {
			return boost::python::object(true);  //ByteNBT(bool) -> Bool
		}
	} catch (std::invalid_argument) {
		;
	}

	std::cout << " [Str]" << std::endl;
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
			//Python list support MIXED list, not need to check

			listnbt.append(inbt);
			if (!this->hasElementSeparator()) {
				break;
			}

			if (!this->reader->canRead()) {
				throw ERROR_EXPECTED_VALUE.createWithContext(this->reader);
			}
			
		}

		this->expect(']');
		return listnbt;
	}
}

boost::python::object JsonToNBT::readArrayTag() {
	this->expect('[');
	int i = this->reader->getCursor();
	char c0 = this->reader->read();
	this->reader->read();
	this->reader->skipWhitespace();
	if (!this->reader->canRead()) {
		throw ERROR_EXPECTED_VALUE.createWithContext(this->reader);
	} else if (c0 == 'B') {
		return this->readArray(7, 1);
	} else if (c0 == 'L') {
		return this->readArray(12, 4);
	} else if (c0 == 'I') {
		return this->readArray(11, 3);
	} else {
		this->reader->setCursor(i);
		throw ERROR_INVALID_ARRAY.createWithContext(this->reader, {c0, 0});
	}
}

boost::python::object JsonToNBT::readArray(short a, short type) {
	boost::python::list list;

	while (true) {
		if (this->reader->peek() != ']') {
			int i = this->reader->getCursor();
			boost::python::object inbt = this->readValue();
			//Python list support MIXED list, not need to check

			//Not converted: Byte | Long | Int
			list.append(inbt);

			if (this->hasElementSeparator()) {
				if (!this->reader->canRead()) {
					throw ERROR_EXPECTED_VALUE.createWithContext(this->reader);
				}
				continue;
			}
		}

		this->expect(']');
		return list;
	}
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