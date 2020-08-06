#ifndef brigadier_HPP_StringReader
#define brigadier_HPP_StringReader

#include <iostream>
#include "ImmutableStringReader.hpp"
using std::string;

namespace brigadier {
	// Subset of https://github.com/Mojang/brigadier/blob/master/src/main/java/com/mojang/brigadier/StringReader.java
	class StringReader : public ImmutableStringReader {
	private:
		static const char SYNTAX_ESCAPE;
		static const char SYNTAX_DOUBLE_QUOTE;
		static const char SYNTAX_SINGLE_QUOTE;
		string str;
		int cursor = 0;
	public:
		StringReader(const StringReader& outher);
		StringReader(string string);
		string getString();
		void setCursor(int cursor);
		int getRemainingLength();
		int getTotalLength();
		int getCursor();
		string getRead();
		string getRemaining();
		bool canRead(int length);
		bool canRead();
		char peek();
		char peek(int offset);
		char read();
		void skip();
		static bool isAllowedNumber(char c);
		static bool isQuotedStringStart(char c);
		void skipWhitespace();
		int readInt();
		long readLong();
		double readDouble();
		float readFloat();
		static bool isAllowedInUnquotedString(char c);
		string readUnquotedString();
		string readQuotedString();
		string readStringUntil(char terminator);
		string readString();
		bool readBoolean();
		void expect(char c);
	};

#ifdef brigadier_IMPLEMENTS

	const char StringReader::SYNTAX_ESCAPE = '\\';
	const char StringReader::SYNTAX_DOUBLE_QUOTE = '"';
	const char StringReader::SYNTAX_SINGLE_QUOTE = '\'';
	
	inline StringReader::StringReader(const StringReader& outher) {
		this->str = outher.str;
		this->cursor = outher.cursor;
	}

	inline StringReader::StringReader(string string) { this->str = string; }

	inline string StringReader::getString() { return this->str; }

	inline void StringReader::setCursor(int cursor) { this->cursor = cursor; }

	inline int StringReader::getRemainingLength() { return this->str.length() - this->cursor; }

	inline int StringReader::getTotalLength() { return this->str.length(); }

	inline int StringReader::getCursor() { return this->cursor; }

	inline string StringReader::getRead() { return this->str.substr(0, this->cursor); }

	inline string StringReader::getRemaining() { return this->str.substr(this->cursor); }

	inline bool StringReader::canRead(int length) { return this->cursor + length <= this->str.length(); }

	inline bool StringReader::canRead() { return this->canRead(1); }

	inline char StringReader::peek() { return this->str.at(this->cursor); }

	inline char StringReader::peek(int offset) { return this->str.at(this->cursor + offset); }

	inline char StringReader::read() { return this->str.at(this->cursor++); }

	inline void StringReader::skip() { ++this->cursor; }

	inline bool StringReader::isAllowedNumber(char c) { return c >= '0' && c <= '9' || c == '.' || c == '-'; }

	inline bool StringReader::isQuotedStringStart(char c) { return c == '"' || c == '\''; }

	void StringReader::skipWhitespace() {
		while (this->canRead() && isspace(this->peek()))
		{
			this->skip();
		}
	}

	int StringReader::readInt() {
		const int start = this->cursor;

		while (this->canRead() && this->isAllowedNumber(this->peek())) {
			this->skip();
		}

		string number = this->str.substr(start, this->cursor - start + 1);
		if (number.empty()) {
			throw const_cast<BuiltInExceptionProvider*>(CommandSyntaxException::BUILT_IN_EXCEPTIONS)->readerExpectedInt().createWithContext(this);
		} 
		else {
			try {
				return std::stoi(number);
			}
			catch (std::invalid_argument) {
				this->cursor = start;
				throw const_cast<BuiltInExceptionProvider*>(CommandSyntaxException::BUILT_IN_EXCEPTIONS)->readerInvalidInt().createWithContext(this, number);
			}
		}
	}

	long StringReader::readLong() {
		const int start = this->cursor;

		while (this->canRead() && this->isAllowedNumber(this->peek())) {
			this->skip();
		}

		string number = this->str.substr(start, this->cursor - start + 1);
		if (number.empty()) {
			throw const_cast<BuiltInExceptionProvider*>(CommandSyntaxException::BUILT_IN_EXCEPTIONS)->readerExpectedLong().createWithContext(this);
		}
		else {
			try {
				return std::stol(number);
			}
			catch (std::invalid_argument) {
				this->cursor = start;
				throw const_cast<BuiltInExceptionProvider*>(CommandSyntaxException::BUILT_IN_EXCEPTIONS)->readerInvalidLong().createWithContext(this, number);
			}
		}
	}

	double StringReader::readDouble() {
		const int start = this->cursor;

		while (this->canRead() && this->isAllowedNumber(this->peek())) {
			this->skip();
		}

		string number = this->str.substr(start, this->cursor - start + 1);
		if (number.empty()) {
			throw const_cast<BuiltInExceptionProvider*>(CommandSyntaxException::BUILT_IN_EXCEPTIONS)->readerExpectedDouble().createWithContext(this);
		}
		else {
			try {
				return std::stol(number);
			}
			catch (std::invalid_argument) {
				this->cursor = start;
				throw const_cast<BuiltInExceptionProvider*>(CommandSyntaxException::BUILT_IN_EXCEPTIONS)->readerInvalidDouble().createWithContext(this, number);
			}
		}
	}

	float StringReader::readFloat() {
		const int start = this->cursor;

		while (this->canRead() && this->isAllowedNumber(this->peek())) {
			this->skip();
		}

		string number = this->str.substr(start, this->cursor - start + 1);
		if (number.empty()) {
			throw const_cast<BuiltInExceptionProvider*>(CommandSyntaxException::BUILT_IN_EXCEPTIONS)->readerExpectedFloat().createWithContext(this);
		}
		else {
			try {
				return std::stol(number);
			}
			catch (std::invalid_argument) {
				this->cursor = start;
				throw const_cast<BuiltInExceptionProvider*>(CommandSyntaxException::BUILT_IN_EXCEPTIONS)->readerInvalidFloat().createWithContext(this, number);
			}
		}
	}

	inline bool StringReader::isAllowedInUnquotedString(char c) {
		return c >= '0' && c <= '9'
			|| c >= 'A' && c <= 'Z'
			|| c >= 'a' && c <= 'z'
			|| c == '_' || c == '-'
			|| c == '.' || c == '+';
	}

	string StringReader::readUnquotedString() {
		const int start = this->cursor;
		while (this->canRead() && isAllowedInUnquotedString(this->peek())) {
			this->skip();
		}
		return this->str.substr(start, this->cursor - start + 1);
	}

	string StringReader::readQuotedString() {
		if (!this->canRead()) {
			return "";
		} else {
			const char next = this->peek();
			if (!isQuotedStringStart(next)) {
				throw const_cast<BuiltInExceptionProvider*>(CommandSyntaxException::BUILT_IN_EXCEPTIONS)->readerExpectedStartOfQuote().createWithContext(this);
			}
			this->skip();
			return this->readStringUntil(next);
		}
	}

	string StringReader::readStringUntil(char terminator) {
		StringBuilder<char> result;
		bool escaped = false;
		while (this->canRead()) {
			const char c = this->read();
			if (escaped) {
				if (c == terminator || c == SYNTAX_ESCAPE) {
					result.Append({c,0});
					escaped = false;
				} else {
					this->setCursor(this->getCursor() - 1);
					throw const_cast<BuiltInExceptionProvider*>(CommandSyntaxException::BUILT_IN_EXCEPTIONS)->readerInvalidEscape().createWithContext(this, string({ c,0 }));
				}
			} else if (c == SYNTAX_ESCAPE) {
				escaped = true;
			} else if (c == terminator) {
				return result.ToString();
			} else {
				result.Append({ c,0 });
;			}
		}
		
		throw const_cast<BuiltInExceptionProvider*>(CommandSyntaxException::BUILT_IN_EXCEPTIONS)->readerExpectedEndOfQuote().createWithContext(this);
	}

	string StringReader::readString() {
		if (!this->canRead()) {
			return "";
		}
		const char next = this->peek();
		if (isQuotedStringStart(next)) {
			this->skip();
			return this->readStringUntil(next);
		}
		return this->readUnquotedString();
	}

	bool StringReader::readBoolean() {
		const int start = this->cursor;
		const string value = this->readString();
		if (value.empty()) {
			throw const_cast<BuiltInExceptionProvider*>(CommandSyntaxException::BUILT_IN_EXCEPTIONS)->readerExpectedBool().createWithContext(this);
		}

		if (value.compare("true")) {
			return true;
		} else if (value.compare("false")) {
			return false;
		} else {
			this->cursor = start;
			throw const_cast<BuiltInExceptionProvider*>(CommandSyntaxException::BUILT_IN_EXCEPTIONS)->readerInvalidBool().createWithContext(this, value);
		}
	}

	void StringReader::expect(char c) {
		if (!this->canRead() || this->peek() != c) {
			throw const_cast<BuiltInExceptionProvider*>(CommandSyntaxException::BUILT_IN_EXCEPTIONS)->readerExpectedSymbol().createWithContext(this, string({ c,0 }));
		}
	}

#endif

}

#endif