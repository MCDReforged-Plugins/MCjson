#ifndef brigadier_HPP_Message
#define brigadier_HPP_Message

//using std::string;

namespace brigadier {
	//Subset of https://github.com/Mojang/brigadier/blob/master/src/main/java/com/mojang/brigadier/Message.java
	class Message {
	public:
		virtual std::string getString() const = 0;
		virtual Message* clone() const = 0; //return new obj
		virtual ~Message();
	};

	class LiteralMessage : public Message {
	private:
		std::string str;
	public:
		LiteralMessage(const std::string& s);
		Message* clone() const override;
		std::string getString() const override;
		std::string toString() const;
	};

#ifdef brigadier_IMPLEMENTS

	Message::~Message() {}
	
	LiteralMessage::LiteralMessage(const std::string& s) { this->str = s; }

	Message* LiteralMessage::clone() const {
		return new LiteralMessage(*this);
	}

	std::string LiteralMessage::getString() const { return this->str; }

	std::string LiteralMessage::toString() const { return this->str; }

#endif

}
#endif