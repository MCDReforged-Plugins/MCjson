#ifndef brigadier_HPP_StringReader
#define brigadier_HPP_StringReader

#include <iostream>
#include "ImmutableStringReader.hpp"
//using std::string;

namespace brigadier {
	// Subset of https://github.com/Mojang/brigadier/blob/master/src/main/java/com/mojang/brigadier/StringReader.java
	class StringReader : public ImmutableStringReader {
	private:
		static const char SYNTAX_ESCAPE;
		static const char SYNTAX_DOUBLE_QUOTE;
		static const char SYNTAX_SINGLE_QUOTE;
		std::string str;
		int cursor = 0;
	public:
		StringReader();
		StringReader(const StringReader& outher);
		StringReader(std::string s);
		std::string getString() const override;
		void setCursor(int cursor);
		int getRemainingLength() const override;
		int getTotalLength() const override;
		int getCursor() const override;
		std::string getRead() const override;
		std::string getRemaining() const override;
		bool canRead(int length) const override;
		bool canRead() const override;
		char peek() const override;
		char peek(int offset) const override;
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
		std::string readUnquotedString();
		std::string readQuotedString();
		std::string readStringUntil(char terminator);
		std::string readString();
		bool readBoolean();
		void expect(char c);
	};

#ifdef brigadier_IMPLEMENTS
//#pragma message("Build->StringReader")

	const char StringReader::SYNTAX_ESCAPE = '\\';
	const char StringReader::SYNTAX_DOUBLE_QUOTE = '"';
	const char StringReader::SYNTAX_SINGLE_QUOTE = '\'';
	
	StringReader::StringReader(const StringReader& outher) {
		this->str = outher.str;
		this->cursor = outher.cursor;
	}

	StringReader::StringReader() {}
	
	StringReader::StringReader(std::string s) { this->str = s; }

	std::string StringReader::getString() const { return this->str; }

	void StringReader::setCursor(int cursor) { this->cursor = cursor; }

	int StringReader::getRemainingLength() const { return this->str.length() - this->cursor; }

	int StringReader::getTotalLength() const { return this->str.length(); }

	int StringReader::getCursor() const { return this->cursor; }

	std::string StringReader::getRead() const { return this->str.substr(0, this->cursor); }

	std::string StringReader::getRemaining() const { return this->str.substr(this->cursor); }

	bool StringReader::canRead(int length) const { return this->cursor + length <= this->str.length(); }

	bool StringReader::canRead() const { return this->canRead(1); }

	char StringReader::peek() const { return this->str.at(this->cursor); }

	char StringReader::peek(int offset) const { return this->str.at(this->cursor + offset); }

	char StringReader::read() { return this->str.at(this->cursor++); }

	void StringReader::skip() { ++this->cursor; }

	bool StringReader::isAllowedNumber(char c) { return c >= '0' && c <= '9' || c == '.' || c == '-'; }

	bool StringReader::isQuotedStringStart(char c) { return c == '"' || c == '\''; }

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

		std::string number = this->str.substr(start, this->cursor - start + 1);
		if (number.empty()) {
			throw CommandSyntaxException::BUILT_IN_EXCEPTIONS->readerExpectedInt().createWithContext(this);
		} 
		else {
			try {
				return std::stoi(number);
			}
			catch (std::invalid_argument) {
				this->cursor = start;
				throw CommandSyntaxException::BUILT_IN_EXCEPTIONS->readerInvalidInt().createWithContext(this, number);
			}
		}
	}

	long StringReader::readLong() {
		const int start = this->cursor;

		while (this->canRead() && this->isAllowedNumber(this->peek())) {
			this->skip();
		}

		std::string number = this->str.substr(start, this->cursor - start + 1);
		if (number.empty()) {
			throw CommandSyntaxException::BUILT_IN_EXCEPTIONS->readerExpectedLong().createWithContext(this);
		}
		else {
			try {
				return std::stol(number);
			}
			catch (std::invalid_argument) {
				this->cursor = start;
				throw CommandSyntaxException::BUILT_IN_EXCEPTIONS->readerInvalidLong().createWithContext(this, number);
			}
		}
	}

	double StringReader::readDouble() {
		const int start = this->cursor;

		while (this->canRead() && this->isAllowedNumber(this->peek())) {
			this->skip();
		}

		std::string number = this->str.substr(start, this->cursor - start + 1);
		if (number.empty()) {
			throw CommandSyntaxException::BUILT_IN_EXCEPTIONS->readerExpectedDouble().createWithContext(this);
		}
		else {
			try {
				return std::stol(number);
			}
			catch (std::invalid_argument) {
				this->cursor = start;
				throw CommandSyntaxException::BUILT_IN_EXCEPTIONS->readerInvalidDouble().createWithContext(this, number);
			}
		}
	}

	float StringReader::readFloat() {
		const int start = this->cursor;

		while (this->canRead() && this->isAllowedNumber(this->peek())) {
			this->skip();
		}

		std::string number = this->str.substr(start, this->cursor - start + 1);
		if (number.empty()) {
			throw CommandSyntaxException::BUILT_IN_EXCEPTIONS->readerExpectedFloat().createWithContext(this);
		}
		else {
			try {
				return std::stol(number);
			}
			catch (std::invalid_argument) {
				this->cursor = start;
				throw CommandSyntaxException::BUILT_IN_EXCEPTIONS->readerInvalidFloat().createWithContext(this, number);
			}
		}
	}

	bool StringReader::isAllowedInUnquotedString(char c) {
		return c >= '0' && c <= '9'
			|| c >= 'A' && c <= 'Z'
			|| c >= 'a' && c <= 'z'
			|| c == '_' || c == '-'
			|| c == '.' || c == '+';
	}

	std::string StringReader::readUnquotedString() {
		const int start = this->cursor;
		while (this->canRead() && isAllowedInUnquotedString(this->peek())) {
			this->skip();
		}
		return this->str.substr(start, this->cursor - start + 1);
	}

	std::string StringReader::readQuotedString() {
		if (!this->canRead()) {
			return "";
		} else {
			const char next = this->peek();
			if (!isQuotedStringStart(next)) {
				throw CommandSyntaxException::BUILT_IN_EXCEPTIONS->readerExpectedStartOfQuote().createWithContext(this);
			}
			this->skip();
			return this->readStringUntil(next);
		}
	}

	std::string StringReader::readStringUntil(char terminator) {
		StringBuilder<char> result;
		bool escaped = false;
		
		while (this->canRead()) {
			const char c = this->read();
			if (escaped) {
				if (c != terminator && c != SYNTAX_ESCAPE) {
					this->setCursor(this->getCursor() - 1);
					throw CommandSyntaxException::BUILT_IN_EXCEPTIONS->readerInvalidEscape().createWithContext(this, std::string({ c,0 }));
				}
				
				result.Append(std::string({c,0}).c_str());
				escaped = false;
			} else if (c == SYNTAX_ESCAPE) {
				escaped = true;
			} else if (c == terminator) {
				return result.ToString();
			} else {
				result.Append(std::string({ c,0 }).c_str());
;			}
		}
		
		throw CommandSyntaxException::BUILT_IN_EXCEPTIONS->readerExpectedEndOfQuote().createWithContext(this);
	}

	std::string StringReader::readString() {
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
		const std::string value = this->readString();
		if (value.empty()) {
			throw CommandSyntaxException::BUILT_IN_EXCEPTIONS->readerExpectedBool().createWithContext(this);
		}

		if (value.compare("true")) {
			return true;
		} else if (value.compare("false")) {
			return false;
		} else {
			this->cursor = start;
			throw CommandSyntaxException::BUILT_IN_EXCEPTIONS->readerInvalidBool().createWithContext(this, value);
		}
	}

	void StringReader::expect(char c) {
		if (this->canRead() && this->peek() == c) {
			this->skip();
		} else {
			throw CommandSyntaxException::BUILT_IN_EXCEPTIONS->readerExpectedSymbol().createWithContext(this, std::string({ c,0 }));
		}
	}

#endif

}

#endif