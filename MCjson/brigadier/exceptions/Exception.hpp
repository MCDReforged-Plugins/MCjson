#ifndef brigadier_HPP_Exception

#include<iostream>
#include<string>
#include<exception>
#include<algorithm>
#include "..\ImmutableStringReader.hpp"
#include "..\StringBuilder.hpp"
#include "..\Message.hpp"

using std::string;

//Statement

namespace brigadier {
	class BuiltInExceptionProvider; //Include from BuiltInExceptions.hpp
	class Exception{
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

	class CommandSyntaxException : public Exception {
	private:
		CommandExceptionType* type = 0;
		Message* message = 0;
		string input;
		int cursor = 0;
	public:
		static const int CONTEXT_AMOUNT;
		static const BuiltInExceptionProvider* BUILT_IN_EXCEPTIONS;
		CommandSyntaxException(const CommandExceptionType* type, const Message* message);
		CommandSyntaxException(const CommandExceptionType* type, const Message* message, const string& input, const int cursor);
		CommandSyntaxException(const CommandSyntaxException& outher);
		~CommandSyntaxException() override;
		const Message* getRawMessage() override;
		string getInput();
		const int getCursor();
		const CommandExceptionType* getType();
		string getContext();
		string getMessage() override;
		string getTypeString() override;
	};
	
	class SimpleCommandExceptionType : public CommandExceptionType {
	private:
		Message* message = 0;
	public:
		SimpleCommandExceptionType(const Message* message);
		SimpleCommandExceptionType(const SimpleCommandExceptionType& outher);
		~SimpleCommandExceptionType() override;
		string getTypeString();
		CommandExceptionType* clone() override;
		CommandSyntaxException create();
		CommandSyntaxException createWithContext(const ImmutableStringReader* reader);
		string toString();
	};

	namespace ExceptionFunction {
		typedef Message* (*DynamicCommandFunction)(const string&);
		typedef Message* (*Dynamic2CommandFunction)(const string&, const string&);
		typedef Message* (*Dynamic3CommandFunction)(const string&, const string&, const string&);
		typedef Message* (*Dynamic4CommandFunction)(const string&, const string&, const string&, const string&);
		/*
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
		*/
	}

	class DynamicCommandExceptionType : public CommandExceptionType {
	private:
		ExceptionFunction::DynamicCommandFunction function = 0;
	public:
		DynamicCommandExceptionType(const ExceptionFunction::DynamicCommandFunction& function);
		CommandExceptionType* clone() override;
		CommandSyntaxException create(const string& arg);
		CommandSyntaxException createWithContext(const ImmutableStringReader* reader, const string& arg);
	};

	class Dynamic2CommandExceptionType : public CommandExceptionType {
	private:
		ExceptionFunction::Dynamic2CommandFunction function = 0;
	public:
		Dynamic2CommandExceptionType(const ExceptionFunction::Dynamic2CommandFunction function);
		CommandExceptionType* clone() override;
		CommandSyntaxException create(const string& a, const string& b);
		CommandSyntaxException createWithContext(const ImmutableStringReader* reader, const string& a, const string& b);
	};

	class Dynamic3CommandExceptionType : public CommandExceptionType {
	private:
		ExceptionFunction::Dynamic3CommandFunction function = 0;
	public:
		Dynamic3CommandExceptionType(ExceptionFunction::Dynamic3CommandFunction function);
		CommandExceptionType* clone() override;
		CommandSyntaxException create(const string& a, const string& b, const string& c);
		CommandSyntaxException createWithContext(const ImmutableStringReader* reader, const string& a, const string& b, const string& c);
	};

	class Dynamic4CommandExceptionType : public CommandExceptionType {
	private:
		ExceptionFunction::Dynamic4CommandFunction function = 0;
	public:
		Dynamic4CommandExceptionType(ExceptionFunction::Dynamic4CommandFunction function);
		CommandExceptionType* clone() override;
		CommandSyntaxException create(const string& a, const string& b, const string& c, const string& d);
		CommandSyntaxException createWithContext(const ImmutableStringReader* reader, const string& a, const string& b, const string& c, const string& d);
	};
}

//Implementation

#ifdef brigadier_IMPLEMENTS
namespace brigadier {
	
	const int CommandSyntaxException::CONTEXT_AMOUNT = 10;
	
	CommandSyntaxException::CommandSyntaxException(const CommandExceptionType* type, const Message* message) {
		this->type = const_cast<CommandExceptionType*>(type);
		this->message = const_cast<Message*>(message);
	}

	CommandSyntaxException::CommandSyntaxException(const CommandExceptionType* type, const Message* message, const string& input, const int cursor) {
		this->type = const_cast<CommandExceptionType*>(type);
		this->message = const_cast<Message*>(message);
		this->input = input;
		this->cursor = cursor;
	}

	CommandSyntaxException::CommandSyntaxException(const CommandSyntaxException& outher) {
		//get new obj for type/message
		this->type = outher.type->clone();
		this->message = outher.message->clone();
		this->input = outher.input;
		this->cursor = outher.cursor;
	}

	CommandSyntaxException::~CommandSyntaxException() {
		delete this->type;
		delete this->message;
	}

	const Message* CommandSyntaxException::getRawMessage() { return this->message; }

	string CommandSyntaxException::getInput() { return this->input; }

	 const int CommandSyntaxException::getCursor() { return this->cursor; }

	const CommandExceptionType* CommandSyntaxException::getType() { return this->type; }

	string CommandSyntaxException::getContext() {
		if (this->input.length() > 0 && this->cursor >= 0) {
			StringBuilder<char> builder;
			int cursor = std::min((int)this->input.length(), this->cursor);
			if (cursor > 10) {
				builder.Append("...");
			}

			//substring at java: builder.append(this.input.substring(Math.max(0, cursor - 10), cursor));
			//Java(4, 8)[begin, end] -> C++(4, 4)[begin, length = end - begin + 1]
			builder.Append(this->input.substr(std::max(0, cursor - CONTEXT_AMOUNT), cursor - std::max(0, cursor - CONTEXT_AMOUNT) + 1));
			builder.Append("<--[HERE]");
			return builder.ToString();
		} else {
			return string();
		}
	}

	string CommandSyntaxException::getMessage() {
		string message = this->message->getString();
		string context = this->getContext();
		if (!context.empty()) {
			message = message + " at position " + std::to_string(this->cursor) + ": " + context;
		}

		return message;
	}

	string CommandSyntaxException::getTypeString() {
		return string("CommandSyntaxException");
	}

	SimpleCommandExceptionType::SimpleCommandExceptionType( const Message* message) {this->message = const_cast<Message*>(message); }

	SimpleCommandExceptionType::SimpleCommandExceptionType(const SimpleCommandExceptionType& outher) { this->message = outher.message->clone(); }

	SimpleCommandExceptionType::~SimpleCommandExceptionType() { delete this->message; }

	string SimpleCommandExceptionType::getTypeString() { return string("SimpleCommandExceptionType"); }

	CommandExceptionType* SimpleCommandExceptionType::clone() { return new SimpleCommandExceptionType(*this); }

	CommandSyntaxException SimpleCommandExceptionType::create() { return CommandSyntaxException(this->clone(), this->message->clone()); }

	CommandSyntaxException SimpleCommandExceptionType::createWithContext(const ImmutableStringReader* reader) {
		return CommandSyntaxException(this->clone(), this->message->clone(), const_cast<ImmutableStringReader*>(reader)->getString(), const_cast<ImmutableStringReader*>(reader)->getCursor());
	}

	string SimpleCommandExceptionType::toString() { return this->message->getString(); }

	DynamicCommandExceptionType::DynamicCommandExceptionType(const ExceptionFunction::DynamicCommandFunction& function) { this->function = function; };

	CommandExceptionType* DynamicCommandExceptionType::clone() { return new DynamicCommandExceptionType(*this); }

	CommandSyntaxException DynamicCommandExceptionType::create(const string& arg) {
		return CommandSyntaxException(this->clone(), this->function(arg));
	}

	CommandSyntaxException DynamicCommandExceptionType::createWithContext(const ImmutableStringReader* reader, const string& arg) {
		return CommandSyntaxException(new DynamicCommandExceptionType(*this), this->function(arg), const_cast<ImmutableStringReader*>(reader)->getString(), const_cast<ImmutableStringReader*>(reader)->getCursor());
	}

	Dynamic2CommandExceptionType::Dynamic2CommandExceptionType(ExceptionFunction::Dynamic2CommandFunction function) { this->function = function; };

	CommandExceptionType* Dynamic2CommandExceptionType::clone() { return new Dynamic2CommandExceptionType(*this); }

	CommandSyntaxException Dynamic2CommandExceptionType::create(const string& a, const string& b) {
		return CommandSyntaxException(this->clone(), this->function(a, b));
	}

	CommandSyntaxException Dynamic2CommandExceptionType::createWithContext(const ImmutableStringReader* reader, const string& a, const string& b) {
		return CommandSyntaxException(new Dynamic2CommandExceptionType(*this), this->function(a, b), const_cast<ImmutableStringReader*>(reader)->getString(), const_cast<ImmutableStringReader*>(reader)->getCursor());
	}

	Dynamic3CommandExceptionType::Dynamic3CommandExceptionType(ExceptionFunction::Dynamic3CommandFunction function) { this->function = function; };

	CommandExceptionType* Dynamic3CommandExceptionType::clone() { return new Dynamic3CommandExceptionType(*this); }

	CommandSyntaxException Dynamic3CommandExceptionType::create(const string& a, const string& b, const string& c) {
		return CommandSyntaxException(this->clone(), this->function(a, b, c));
	}

	 CommandSyntaxException Dynamic3CommandExceptionType::createWithContext(const ImmutableStringReader* reader, const string& a, const string& b, const string& c) {
		return CommandSyntaxException(new Dynamic3CommandExceptionType(*this), this->function(a, b, c), const_cast<ImmutableStringReader*>(reader)->getString(), const_cast<ImmutableStringReader*>(reader)->getCursor());
	}

	Dynamic4CommandExceptionType::Dynamic4CommandExceptionType(ExceptionFunction::Dynamic4CommandFunction function) { this->function = function; };

	CommandExceptionType* Dynamic4CommandExceptionType::clone() { return new Dynamic4CommandExceptionType(*this); }

	CommandSyntaxException Dynamic4CommandExceptionType::create(const string& a, const string& b, const string& c, const string& d) {
		return CommandSyntaxException(this->clone(), this->function(a, b, c, d));
	}

	CommandSyntaxException Dynamic4CommandExceptionType::createWithContext(const ImmutableStringReader* reader, const string& a, const string& b, const string& c, const string& d) {
		return CommandSyntaxException(new Dynamic4CommandExceptionType(*this), this->function(a, b, c, d), const_cast<ImmutableStringReader*>(reader)->getString(), const_cast<ImmutableStringReader*>(reader)->getCursor());
	}
}
#endif

#define brigadier_HPP_Exception
#endif

//Initialization BUILT_IN_EXCEPTIONS when included BuiltInExceptions.hpp
#ifdef brigadier_HPP_BuiltInExceptions
#ifndef brigadier_HPP_Exception_BUILT_IN_EXCEPTIONS
#ifdef brigadier_IMPLEMENTS
const brigadier::BuiltInExceptionProvider* brigadier::CommandSyntaxException::BUILT_IN_EXCEPTIONS = new BuiltInExceptions();
#define brigadier_HPP_Exception_BUILT_IN_EXCEPTIONS
#endif
#endif
#endif