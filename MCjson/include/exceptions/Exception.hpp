#pragma once

#include<iostream>
#include<string>
#include<algorithm>
#include<StringBuilder.hpp>
#include<Message.hpp>
#include<exceptions/CommandExceptionType.hpp>

using std::string;

namespace brigadier {
	class Exception {
	public:
		virtual string getMessage() = 0;
		virtual const Message* getRawMessage() = 0;
	};

	class CommandSyntaxException : public Exception {
	private:
		CommandExceptionType* type;
		Message* message;
		string input;
		int cursor = 0;
	public:
		const int CONTEXT_AMOUNT = 10;
		CommandSyntaxException(CommandExceptionType* type, Message* message);
		CommandSyntaxException(CommandExceptionType* type, Message* message, string& input, int cursor);
		~CommandSyntaxException();
		const Message* getRawMessage();
		string getInput();
		const int getCursor();
		const CommandExceptionType* getType();
		string getContext();
		string getMessage();
	};

	inline CommandSyntaxException::CommandSyntaxException(CommandExceptionType* type, Message* message) {
		this->type = type;
		this->message = message;
	}

	inline CommandSyntaxException::CommandSyntaxException(CommandExceptionType* type, Message* message, string& input, int cursor) {
		this->type = type;
		this->message = message;
		this->input = input;
		this->cursor = cursor;
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
}