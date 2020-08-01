#ifndef brigadier_HPP_StringReader
#define brigadier_HPP_StringReader

#include <iostream>

using std::string;

namespace brigadier {
	// Subset of https://github.com/Mojang/brigadier/blob/master/src/main/java/com/mojang/brigadier/ImmutableStringReader.java
	class ImmutableStringReader {
	public:
		virtual string getString() = 0;
		virtual int getRemainingLength() = 0;
		virtual int getTotalLength() = 0;
		virtual int getCursor() = 0;
		virtual string getRead() = 0;
		virtual string getRemaining() = 0;
		virtual bool canRead(int var1) = 0;
		virtual bool canRead() = 0;
		virtual char peek() = 0;
		virtual char peek(int var1) = 0;
	};

	// Subset of https://github.com/Mojang/brigadier/blob/master/src/main/java/com/mojang/brigadier/StringReader.java
	class StringReader : public ImmutableStringReader {
	private:
		const char SYNTAX_ESCAPE = '\\';
		const char SYNTAX_DOUBLE_QUOTE = '"';
		const char SYNTAX_SINGLE_QUOTE = '\'';
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
		string readQuotedString();
		string readStringUntil(char terminator);
		string readString();
		bool readBoolean();
		void expect(char c);
	};

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
		int start = this->cursor;

		while (this->canRead() && this->isAllowedNumber(this->peek())) {
			this->skip();
		}

		string number = this->str.substr(start, this->cursor - start + 1);
		if (number.empty()) {
			
		};
	}

}

#endif