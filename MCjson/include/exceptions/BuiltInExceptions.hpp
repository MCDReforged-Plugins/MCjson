#ifndef brigadier_HPP_BuiltInExceptionProvider
#define brigadier_HPP_BuiltInExceptionProvider

#include "Exception.hpp"

namespace brigadier {

	
	class BuiltInExceptionProvider {
	public:
		virtual Dynamic2CommandExceptionType doubleTooLow() = 0;
		virtual Dynamic2CommandExceptionType doubleTooHigh() = 0;
		virtual Dynamic2CommandExceptionType floatTooLow() = 0;
		virtual Dynamic2CommandExceptionType floatTooHigh() = 0;
		virtual Dynamic2CommandExceptionType integerTooLow() = 0;
		virtual Dynamic2CommandExceptionType integerTooHigh() = 0;
		virtual Dynamic2CommandExceptionType longTooLow() = 0;
		virtual Dynamic2CommandExceptionType longTooHigh() = 0;
		virtual DynamicCommandExceptionType literalIncorrect() = 0;
		virtual SimpleCommandExceptionType readerExpectedStartOfQuote() = 0;
		virtual SimpleCommandExceptionType readerExpectedEndOfQuote() = 0;
		virtual DynamicCommandExceptionType readerInvalidEscape() = 0;
		virtual DynamicCommandExceptionType readerInvalidBool() = 0;
		virtual DynamicCommandExceptionType readerInvalidInt() = 0;
		virtual SimpleCommandExceptionType readerExpectedInt() = 0;
		virtual DynamicCommandExceptionType readerInvalidLong() = 0;
		virtual SimpleCommandExceptionType readerExpectedLong() = 0;
		virtual DynamicCommandExceptionType readerInvalidDouble() = 0;
		virtual SimpleCommandExceptionType readerExpectedDouble() = 0;
		virtual DynamicCommandExceptionType readerInvalidFloat() = 0;
		virtual SimpleCommandExceptionType readerExpectedFloat() = 0;
		virtual SimpleCommandExceptionType readerExpectedBool() = 0;
		virtual DynamicCommandExceptionType readerExpectedSymbol() = 0;
		virtual SimpleCommandExceptionType dispatcherUnknownCommand() = 0;
		virtual SimpleCommandExceptionType dispatcherUnknownArgument() = 0;
		virtual SimpleCommandExceptionType dispatcherExpectedArgumentSeparator() = 0;
		virtual DynamicCommandExceptionType dispatcherParseException() = 0;
	};

	class BuiltInExceptions : public BuiltInExceptionProvider {
	
	};

}

#endif