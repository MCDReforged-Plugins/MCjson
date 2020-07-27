#pragma once

#include<iostream>
#include<StringReader.hpp>
#include<Message.hpp>

using std::string;

namespace brigadier {
	class CommandExceptionType {
	public:
		virtual string getTypeString() = 0;
		virtual CommandExceptionType* clone() = 0;
	};

	class Dynamic2CommandExceptionType : public CommandExceptionType {

	};
}