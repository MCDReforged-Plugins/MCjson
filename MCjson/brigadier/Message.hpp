#ifndef brigadier_HPP_Message
#define brigadier_HPP_Message

#include<iostream>

using std::string;

namespace brigadier {
	class Message {
	public:
		virtual string getString() = 0;
		virtual Message* clone() = 0; //return new obj
	};

	class LiteralMessage : public Message {
	private:
		string str;
	public:
		LiteralMessage(const string& s);
		Message* clone() override;
		string getString() override;
		string toString();
	};

#ifdef brigadier_IMPLEMENTS

	LiteralMessage::LiteralMessage(const string& s) { this->str = s; }

	Message* LiteralMessage::clone() {
		return new LiteralMessage(*this);
	}

	string LiteralMessage::getString() { return this->str; }

	string LiteralMessage::toString() { return this->str; }

#endif

}
#endif