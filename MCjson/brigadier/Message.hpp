#ifndef brigadier_HPP_Message
#define brigadier_HPP_Message

//using std::string;

namespace brigadier {
	//Subset of https://github.com/Mojang/brigadier/blob/master/src/main/java/com/mojang/brigadier/Message.java
	class Message {
	public:
		virtual std::string getString() = 0;
		virtual Message* clone() = 0; //return new obj
	};

	class LiteralMessage : public Message {
	private:
		std::string str;
	public:
		LiteralMessage(const std::string& s);
		Message* clone() override;
		std::string getString() override;
		std::string toString();
	};

#ifdef brigadier_IMPLEMENTS

	LiteralMessage::LiteralMessage(const std::string& s) { this->str = s; }

	Message* LiteralMessage::clone() {
		return new LiteralMessage(*this);
	}

	std::string LiteralMessage::getString() { return this->str; }

	std::string LiteralMessage::toString() { return this->str; }

#endif

}
#endif