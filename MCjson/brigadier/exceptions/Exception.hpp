#ifndef brigadier_HPP_Exception

#include<exception>
#include<algorithm>
#include "..\ImmutableStringReader.hpp"
#include "..\StringBuilder.hpp"
#include "..\Message.hpp"

//using std::string;

//Statement

namespace brigadier {
	//Subset of https://github.com/Mojang/brigadier/tree/master/src/main/java/com/mojang/brigadier/exceptions
	class BuiltInExceptionProvider; //Include from BuiltInExceptions.hpp
	class Exception{
	public:
		
		virtual std::string getMessage() const = 0;
		virtual const Message* getRawMessage() const = 0;
		virtual std::string getTypeString() const = 0;
		virtual ~Exception() {};
	};

	class CommandExceptionType {
	public:
		virtual CommandExceptionType* clone() const = 0; //return new obj
		virtual ~CommandExceptionType() {};
	};

	class CommandSyntaxException : public Exception {
	private:
		const CommandExceptionType* type = 0;
		const Message* message = 0;
		std::string input;
		int cursor = 0;
	public:
		static const int CONTEXT_AMOUNT;
		static const BuiltInExceptionProvider* BUILT_IN_EXCEPTIONS;
		CommandSyntaxException(const CommandExceptionType* type, const Message* message);
		CommandSyntaxException(const CommandExceptionType* type, const Message* message, const std::string& input, const int& cursor);
		CommandSyntaxException(const CommandSyntaxException& outher);
		~CommandSyntaxException() override;
		const Message* getRawMessage() const override;
		std::string getInput() const;
		int getCursor() const;
		const CommandExceptionType* getType();
		std::string getContext() const;
		std::string getMessage() const override;
		std::string getTypeString() const override;
	};
	
	class SimpleCommandExceptionType : public CommandExceptionType {
	private:
		const Message* message = 0;
	public:
		SimpleCommandExceptionType(const Message* message);
		SimpleCommandExceptionType(const SimpleCommandExceptionType& outher);
		~SimpleCommandExceptionType() override;
		std::string getTypeString() const;
		CommandExceptionType* clone() const override;
		CommandSyntaxException create() const;
		CommandSyntaxException createWithContext(const ImmutableStringReader* reader) const;
		std::string toString() const;
	};

	namespace ExceptionFunction {
		typedef Message* (*DynamicCommandFunction)(const std::string&);
		typedef Message* (*Dynamic2CommandFunction)(const std::string&, const std::string&);
		typedef Message* (*Dynamic3CommandFunction)(const std::string&, const std::string&, const std::string&);
		typedef Message* (*Dynamic4CommandFunction)(const std::string&, const std::string&, const std::string&, const std::string&);
		/*
		class DynamicCommandFunction {
		public:
			virtual Message* apply(const std::string& var) = 0;
		};

		class Dynamic2CommandFunction {
		public:
			virtual Message* apply(const std::string& var1, const std::string& var2) = 0;
		};

		class Dynamic3CommandFunction {
		public:
			virtual Message* apply(const std::string& var1, const std::string& var2, const std::string& var3) = 0;
		};

		class Dynamic4CommandFunction {
		public:
			virtual Message* apply(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4) = 0;
		};
		*/
	}

	class DynamicCommandExceptionType : public CommandExceptionType {
	private:
		ExceptionFunction::DynamicCommandFunction function = 0;
	public:
		DynamicCommandExceptionType(const ExceptionFunction::DynamicCommandFunction& function);
		CommandExceptionType* clone() const override;
		CommandSyntaxException create(const std::string& arg) const;
		CommandSyntaxException createWithContext(const ImmutableStringReader* reader, const std::string& arg) const;
	};

	class Dynamic2CommandExceptionType : public CommandExceptionType {
	private:
		ExceptionFunction::Dynamic2CommandFunction function = 0;
	public:
		Dynamic2CommandExceptionType(const ExceptionFunction::Dynamic2CommandFunction function);
		CommandExceptionType* clone() const override;
		CommandSyntaxException create(const std::string& a, const std::string& b) const;
		CommandSyntaxException createWithContext(const ImmutableStringReader* reader, const std::string& a, const std::string& b) const;
	};

	class Dynamic3CommandExceptionType : public CommandExceptionType {
	private:
		ExceptionFunction::Dynamic3CommandFunction function = 0;
	public:
		Dynamic3CommandExceptionType(ExceptionFunction::Dynamic3CommandFunction function);
		CommandExceptionType* clone() const override;
		CommandSyntaxException create(const std::string& a, const std::string& b, const std::string& c) const;
		CommandSyntaxException createWithContext(const ImmutableStringReader* reader, const std::string& a, const std::string& b, const std::string& c) const;
	};

	class Dynamic4CommandExceptionType : public CommandExceptionType {
	private:
		ExceptionFunction::Dynamic4CommandFunction function = 0;
	public:
		Dynamic4CommandExceptionType(ExceptionFunction::Dynamic4CommandFunction function);
		CommandExceptionType* clone() const override;
		CommandSyntaxException create(const std::string& a, const std::string& b, const std::string& c, const std::string& d) const;
		CommandSyntaxException createWithContext(const ImmutableStringReader* reader, const std::string& a, const std::string& b, const std::string& c, const std::string& d) const;
	};
}

//Implementation

#ifdef brigadier_IMPLEMENTS
namespace brigadier {
	
	const int CommandSyntaxException::CONTEXT_AMOUNT = 10;
	
	CommandSyntaxException::CommandSyntaxException(const CommandExceptionType* type, const Message* message) : type(type), message(message) {}

	CommandSyntaxException::CommandSyntaxException(const CommandExceptionType* type, const Message* message, const std::string& input, const int& cursor) : type(type), message(message), input(input), cursor(cursor) {}

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

	const Message* CommandSyntaxException::getRawMessage() const { return this->message; }

	std::string CommandSyntaxException::getInput() const { return this->input; }

	int CommandSyntaxException::getCursor() const { return this->cursor; }

	const CommandExceptionType* CommandSyntaxException::getType() { return this->type; }

	std::string CommandSyntaxException::getContext() const {
		if (this->input.length() > 0 && this->cursor >= 0) {
			StringBuilder<char> builder;
			int cursor = std::min((int)this->input.length(), this->cursor);
			if (cursor > 10) {
				builder.Append("...");
			}

			//substring at java: builder.append(this.input.substring(Math.max(0, cursor - 10), cursor));
			//Java(4, 8)[begin, end] -> C++(4, 5)[begin, length = end - begin + 1]
			builder.Append(this->input.substr(std::max(0, cursor - CONTEXT_AMOUNT), cursor - std::max(0, cursor - CONTEXT_AMOUNT) + 1));
			builder.Append(" <--[HERE]");
			return builder.ToString();
		} else {
			return std::string();
		}
	}

	std::string CommandSyntaxException::getMessage() const {
		std::string message = this->message->getString();
		std::string context = this->getContext();
		if (!context.empty()) {
			message = message + " at position " + std::to_string(this->cursor) + ": " + context;
		}

		return message;
	}

	std::string CommandSyntaxException::getTypeString() const {
		return std::string("CommandSyntaxException");
	}

	SimpleCommandExceptionType::SimpleCommandExceptionType(const Message* message) : message(message) {}

	SimpleCommandExceptionType::SimpleCommandExceptionType(const SimpleCommandExceptionType& outher) { this->message = outher.message->clone(); }

	SimpleCommandExceptionType::~SimpleCommandExceptionType() { delete this->message; }

	std::string SimpleCommandExceptionType::getTypeString() const { return std::string("SimpleCommandExceptionType"); }

	CommandExceptionType* SimpleCommandExceptionType::clone() const { return new SimpleCommandExceptionType(*this); }

	CommandSyntaxException SimpleCommandExceptionType::create() const { return CommandSyntaxException(this->clone(), this->message->clone()); }

	CommandSyntaxException SimpleCommandExceptionType::createWithContext(const ImmutableStringReader* reader) const {
		return CommandSyntaxException(this->clone(), this->message->clone(), reader->getString(), reader->getCursor());
	}

	std::string SimpleCommandExceptionType::toString() const { return this->message->getString(); }

	DynamicCommandExceptionType::DynamicCommandExceptionType(const ExceptionFunction::DynamicCommandFunction& function) { this->function = function; };

	CommandExceptionType* DynamicCommandExceptionType::clone() const { return new DynamicCommandExceptionType(*this); }

	CommandSyntaxException DynamicCommandExceptionType::create(const std::string& arg) const {
		return CommandSyntaxException(this->clone(), this->function(arg));
	}

	CommandSyntaxException DynamicCommandExceptionType::createWithContext(const ImmutableStringReader* reader, const std::string& arg) const {
		return CommandSyntaxException(new DynamicCommandExceptionType(*this), this->function(arg), reader->getString(), reader->getCursor());
	}

	Dynamic2CommandExceptionType::Dynamic2CommandExceptionType(ExceptionFunction::Dynamic2CommandFunction function) { this->function = function; };

	CommandExceptionType* Dynamic2CommandExceptionType::clone() const { return new Dynamic2CommandExceptionType(*this); }

	CommandSyntaxException Dynamic2CommandExceptionType::create(const std::string& a, const std::string& b) const {
		return CommandSyntaxException(this->clone(), this->function(a, b));
	}

	CommandSyntaxException Dynamic2CommandExceptionType::createWithContext(const ImmutableStringReader* reader, const std::string& a, const std::string& b) const {
		return CommandSyntaxException(new Dynamic2CommandExceptionType(*this), this->function(a, b), reader->getString(), reader->getCursor());
	}

	Dynamic3CommandExceptionType::Dynamic3CommandExceptionType(ExceptionFunction::Dynamic3CommandFunction function) { this->function = function; };

	CommandExceptionType* Dynamic3CommandExceptionType::clone() const { return new Dynamic3CommandExceptionType(*this); }

	CommandSyntaxException Dynamic3CommandExceptionType::create(const std::string& a, const std::string& b, const std::string& c) const {
		return CommandSyntaxException(this->clone(), this->function(a, b, c));
	}

	 CommandSyntaxException Dynamic3CommandExceptionType::createWithContext(const ImmutableStringReader* reader, const std::string& a, const std::string& b, const std::string& c) const {
		return CommandSyntaxException(new Dynamic3CommandExceptionType(*this), this->function(a, b, c), reader->getString(), reader->getCursor());
	}

	Dynamic4CommandExceptionType::Dynamic4CommandExceptionType(ExceptionFunction::Dynamic4CommandFunction function) { this->function = function; };

	CommandExceptionType* Dynamic4CommandExceptionType::clone() const { return new Dynamic4CommandExceptionType(*this); }

	CommandSyntaxException Dynamic4CommandExceptionType::create(const std::string& a, const std::string& b, const std::string& c, const std::string& d) const {
		return CommandSyntaxException(this->clone(), this->function(a, b, c, d));
	}

	CommandSyntaxException Dynamic4CommandExceptionType::createWithContext(const ImmutableStringReader* reader, const std::string& a, const std::string& b, const std::string& c, const std::string& d) const {
		return CommandSyntaxException(new Dynamic4CommandExceptionType(*this), this->function(a, b, c, d), reader->getString(), reader->getCursor());
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