#ifndef brigadier_HPP_Exception
#define brigadier_HPP_Exception

#include<iostream>
#include<string>
#include<algorithm>
#include "..\StringBuilder.hpp"
#include "..\StringReader.hpp"
#include "..\Message.hpp"

using std::string;

//Statement

namespace brigadier {
	class Exception {
	public:
		virtual string getMessage() = 0;
		virtual const Message* getRawMessage() = 0;
		virtual string getTypeString() = 0;
		virtual ~Exception() {};
	};

	class CommandExceptionType {
	public:
		virtual CommandExceptionType* clone() = 0; //return new obj
		virtual ~CommandExceptionType() {};
	};

	class SimpleCommandExceptionType : public CommandExceptionType {
	private:
		const Message* message = 0;
	public:
		SimpleCommandExceptionType(const Message& message);
		SimpleCommandExceptionType(SimpleCommandExceptionType& outher);
		~SimpleCommandExceptionType();
		string getTypeString();
		CommandExceptionType* clone();
		CommandSyntaxException create();
		CommandSyntaxException createWithContext(const ImmutableStringReader* reader);
		string toString();
	};

	namespace ExceptionFunction {
		class DynamicCommandFunction {
		public:
			virtual Message* apply(const string& var) = 0;
		};

		class Dynamic2CommandFunction {
		public:
			virtual Message* apply(const string& var1, const string& var2) = 0;
		};

		class Dynamic3CommandFunction {
		public:
			virtual Message* apply(const string& var1, const string& var2, const string& var3) = 0;
		};

		class Dynamic4CommandFunction {
		public:
			virtual Message* apply(const string& var1, const string& var2, const string& var3, const string& var4) = 0;
		};
	}

	class DynamicCommandExceptionType : public CommandExceptionType {
	private:
		ExceptionFunction::DynamicCommandFunction* function = 0;
	public:
		DynamicCommandExceptionType(ExceptionFunction::DynamicCommandFunction* function);
		~DynamicCommandExceptionType();
		CommandExceptionType* clone();
		CommandSyntaxException create(const string& arg);
		CommandSyntaxException createWithContext(ImmutableStringReader* reader, const string& arg);
	};

	class Dynamic2CommandExceptionType : public CommandExceptionType {

	};

	class Dynamic3CommandExceptionType : public CommandExceptionType {

	};

	class Dynamic4CommandExceptionType : public CommandExceptionType {

	};

	class CommandSyntaxException : public Exception {
	private:
		CommandExceptionType* type = 0;
		Message* message = 0;
		string input;
		int cursor = 0;
	public:
		const int CONTEXT_AMOUNT = 10;
		//static const BuiltInExceptionProvider* const BUILT_IN_EXCEPTIONS = new BuiltInExceptions();
		CommandSyntaxException(const CommandExceptionType* type, const Message* message);
		CommandSyntaxException(const CommandExceptionType* type, const Message* message, const string& input, const int cursor);
		CommandSyntaxException(const CommandSyntaxException& outher);
		~CommandSyntaxException();
		const Message* getRawMessage();
		string getInput();
		const int getCursor();
		const CommandExceptionType* getType();
		string getContext();
		string getMessage();
		string getTypeString();
	};
}

//Implementation

namespace brigadier {
	
	inline CommandSyntaxException::CommandSyntaxException(const CommandExceptionType* type, const Message* message) {
		this->type = const_cast<CommandExceptionType*>(type)->clone();
		this->message = const_cast<Message*>(message)->clone();
	}

	inline CommandSyntaxException::CommandSyntaxException(const CommandExceptionType* type, const Message* message, const string& input, const int cursor) {
		this->type = const_cast<CommandExceptionType*>(type)->clone();
		this->message = const_cast<Message*>(message)->clone();
		this->input = input;
		this->cursor = cursor;
	}

	inline CommandSyntaxException::CommandSyntaxException(const CommandSyntaxException& outher) {
		//get new obj for type/message
		this->type = outher.type->clone();
		this->message = outher.message->clone();
		this->input = outher.input;
		this->cursor = outher.cursor;
	}

	inline CommandSyntaxException::~CommandSyntaxException() {
		delete this->type;
		delete this->message;
	}

	inline const Message* CommandSyntaxException::getRawMessage() { return this->message; }

	inline string CommandSyntaxException::getInput() { return this->input; }

	inline const int CommandSyntaxException::getCursor() { return this->cursor; }

	inline const CommandExceptionType* CommandSyntaxException::getType() { return this->type; }

	string CommandSyntaxException::getContext() {
		if (this->input.length() > 0 && this->cursor >= 0) {
			StringBuilder<char> builder;
			int cursor = std::min((int)this->input.length(), this->cursor);
			if (cursor > 10) {
				builder.Append("...");
			}

			//substring at java: builder.append(this.input.substring(Math.max(0, cursor - 10), cursor));
			//Java(4, 8)[begin, end] -> C++(4, 4)[begin, length = end - begin]
			builder.Append(this->input.substr(std::max(0, cursor - CONTEXT_AMOUNT), cursor - std::max(0, cursor - CONTEXT_AMOUNT)));
			builder.Append("<--[HERE]");
			return builder.ToString();
		} else {
			return string();
		}
	}

	string CommandSyntaxException::getMessage() {
		string message = this->message->getString();
		string context = this->getContext();
		if (context.length()) {
			message = message + " at position " + std::to_string(this->cursor) + ": " + context;
		}

		return message;
	}

	string CommandSyntaxException::getTypeString() {
		return string("CommandSyntaxException");
	}

	inline DynamicCommandExceptionType::DynamicCommandExceptionType(ExceptionFunction::DynamicCommandFunction* function) {
		this->function = function;
	};

	inline DynamicCommandExceptionType::~DynamicCommandExceptionType() {
		delete this->function;
	}

	inline CommandExceptionType* DynamicCommandExceptionType::clone() {
		return new DynamicCommandExceptionType(*this);
	}

	inline CommandSyntaxException DynamicCommandExceptionType::create(const string& arg) {
		return CommandSyntaxException(this->clone(), this->function->apply(arg));
	}

	inline CommandSyntaxException DynamicCommandExceptionType::createWithContext(ImmutableStringReader* reader, const string& arg) {
		return CommandSyntaxException(new DynamicCommandExceptionType(*this), this->function->apply(arg), reader->getString(), reader->getCursor());
	}
}

#endif