#pragma once

#include<iostream>

using std::string;

namespace brigadier {
	class Message {
	public:
		virtual string getString() = 0;
		virtual Message* clone() = 0;
	};

	class LiteralMessage : public Message {
	private:
		string str;
	public:
		LiteralMessage(string& s);
		Message* clone();
		string getString();
		string toString();
	};

	inline LiteralMessage::LiteralMessage(string& s) { this->str = s; }

	Message* LiteralMessage::clone() {
		return new LiteralMessage(*this);
	}

	inline string LiteralMessage::getString() { return this->str; }

	inline string LiteralMessage::toString() { return this->str; }
}