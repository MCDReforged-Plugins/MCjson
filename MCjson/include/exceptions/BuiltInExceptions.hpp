#ifndef brigadier_HPP_BuiltInExceptions
#define brigadier_HPP_BuiltInExceptions

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
	private:
		static const Dynamic2CommandExceptionType DOUBLE_TOO_SMALL;
		static const Dynamic2CommandExceptionType DOUBLE_TOO_BIG;

		static const Dynamic2CommandExceptionType FLOAT_TOO_SMALL;
		static const Dynamic2CommandExceptionType FLOAT_TOO_BIG;

		static const Dynamic2CommandExceptionType INTEGER_TOO_SMALL;
		static const Dynamic2CommandExceptionType INTEGER_TOO_BIG;

		static const Dynamic2CommandExceptionType LONG_TOO_SMALL;
		static const Dynamic2CommandExceptionType LONG_TOO_BIG;

		static const DynamicCommandExceptionType LITERAL_INCORRECT;

		static const SimpleCommandExceptionType READER_EXPECTED_START_OF_QUOTE;
		static const SimpleCommandExceptionType READER_EXPECTED_END_OF_QUOTE;

		static const DynamicCommandExceptionType READER_INVALID_ESCAPE;
		static const DynamicCommandExceptionType READER_INVALID_BOOL;

		static const DynamicCommandExceptionType READER_INVALID_INT;
		static const SimpleCommandExceptionType READER_EXPECTED_INT;

		static const DynamicCommandExceptionType READER_INVALID_LONG;
		static const SimpleCommandExceptionType READER_EXPECTED_LONG;

		static const DynamicCommandExceptionType READER_INVALID_DOUBLE;
		static const SimpleCommandExceptionType READER_EXPECTED_DOUBLE;

		static const DynamicCommandExceptionType READER_INVALID_FLOAT;
		static const SimpleCommandExceptionType READER_EXPECTED_FLOAT;

		static const SimpleCommandExceptionType READER_EXPECTED_BOOL;
		static const DynamicCommandExceptionType READER_EXPECTED_SYMBOL;

		static const SimpleCommandExceptionType DISPATCHER_UNKNOWN_COMMAND;
		static const SimpleCommandExceptionType DISPATCHER_UNKNOWN_ARGUMENT;
		static const SimpleCommandExceptionType DISPATCHER_EXPECTED_ARGUMENT_SEPARATOR;
		static const DynamicCommandExceptionType DISPATCHER_PARSE_EXCEPTION;
	public:
		Dynamic2CommandExceptionType doubleTooLow() override { return DOUBLE_TOO_SMALL; }
		Dynamic2CommandExceptionType doubleTooHigh() override { return DOUBLE_TOO_BIG; }
		Dynamic2CommandExceptionType floatTooLow() override { return FLOAT_TOO_SMALL; }
		Dynamic2CommandExceptionType floatTooHigh() override { return FLOAT_TOO_BIG; }
		Dynamic2CommandExceptionType integerTooLow() override { return INTEGER_TOO_SMALL; }
		Dynamic2CommandExceptionType integerTooHigh() override { return INTEGER_TOO_BIG; }
		Dynamic2CommandExceptionType longTooLow() override { return LONG_TOO_SMALL; }
		Dynamic2CommandExceptionType longTooHigh() override { return LONG_TOO_BIG; }
		DynamicCommandExceptionType literalIncorrect() override { return LITERAL_INCORRECT; }
		SimpleCommandExceptionType readerExpectedStartOfQuote() override { return READER_EXPECTED_START_OF_QUOTE; }
		SimpleCommandExceptionType readerExpectedEndOfQuote() override { return READER_EXPECTED_END_OF_QUOTE; }
		DynamicCommandExceptionType readerInvalidEscape() override { return READER_INVALID_ESCAPE; }
		DynamicCommandExceptionType readerInvalidBool() override { return READER_INVALID_BOOL; }
		DynamicCommandExceptionType readerInvalidInt() override { return READER_INVALID_INT; }
		SimpleCommandExceptionType readerExpectedInt() override { return READER_EXPECTED_INT; }
		DynamicCommandExceptionType readerInvalidLong() override { return READER_INVALID_LONG; }
		SimpleCommandExceptionType readerExpectedLong() override { return READER_EXPECTED_LONG; }
		DynamicCommandExceptionType readerInvalidDouble() override { return READER_INVALID_DOUBLE; }
		SimpleCommandExceptionType readerExpectedDouble() override { return READER_EXPECTED_DOUBLE; }
		DynamicCommandExceptionType readerInvalidFloat() override { return READER_INVALID_FLOAT; }
		SimpleCommandExceptionType readerExpectedFloat() override { return READER_EXPECTED_FLOAT; }
		SimpleCommandExceptionType readerExpectedBool() override { return READER_EXPECTED_BOOL; }
		DynamicCommandExceptionType readerExpectedSymbol() override { return READER_EXPECTED_SYMBOL; }
		SimpleCommandExceptionType dispatcherUnknownCommand() override { return DISPATCHER_UNKNOWN_COMMAND; }
		SimpleCommandExceptionType dispatcherUnknownArgument() override { return DISPATCHER_UNKNOWN_ARGUMENT; }
		SimpleCommandExceptionType dispatcherExpectedArgumentSeparator() override { return DISPATCHER_EXPECTED_ARGUMENT_SEPARATOR; }
		DynamicCommandExceptionType dispatcherParseException() override { return DISPATCHER_PARSE_EXCEPTION; }
	};

	
	const Dynamic2CommandExceptionType BuiltInExceptions::DOUBLE_TOO_SMALL = Dynamic2CommandExceptionType([](const string& found, const string& min)->Message* {
		return new LiteralMessage("Double must not be less than " + min + ", found " + found); 
		});

	const Dynamic2CommandExceptionType BuiltInExceptions::DOUBLE_TOO_BIG = Dynamic2CommandExceptionType([](const string& found, const string& max)->Message* {
		return new LiteralMessage("Double must not be more than " + max + ", found " + found);
		});

	const Dynamic2CommandExceptionType BuiltInExceptions::FLOAT_TOO_SMALL = Dynamic2CommandExceptionType([](const string& found, const string& min)->Message* {
		return new LiteralMessage("Float must not be less than " + min + ", found " + found);
		});

	const Dynamic2CommandExceptionType BuiltInExceptions::FLOAT_TOO_BIG = Dynamic2CommandExceptionType([](const string& found, const string& max)->Message* {
		return new LiteralMessage("Float must not be more than " + max + ", found " + found);
		});

	const Dynamic2CommandExceptionType BuiltInExceptions::INTEGER_TOO_SMALL = Dynamic2CommandExceptionType([](const string& found, const string& min)->Message* {
		return new LiteralMessage("Integer must not be less than " + min + ", found " + found);
		});

	const Dynamic2CommandExceptionType BuiltInExceptions::INTEGER_TOO_BIG = Dynamic2CommandExceptionType([](const string& found, const string& max)->Message* {
		return new LiteralMessage("Integer must not be more than " + max + ", found " + found);
		});

	const Dynamic2CommandExceptionType BuiltInExceptions::LONG_TOO_SMALL = Dynamic2CommandExceptionType([](const string& found, const string& min)->Message* {
		return new LiteralMessage("Long must not be less than " + min + ", found " + found);
		});

	const Dynamic2CommandExceptionType BuiltInExceptions::LONG_TOO_BIG = Dynamic2CommandExceptionType([](const string& found, const string& max)->Message* {
		return new LiteralMessage("Long must not be more than " + max + ", found " + found);
		});
	
	const DynamicCommandExceptionType BuiltInExceptions::LITERAL_INCORRECT = DynamicCommandExceptionType([](const string& expected)->Message* {
		return new LiteralMessage("Expected literal " + expected); 
		});

	const SimpleCommandExceptionType BuiltInExceptions::READER_EXPECTED_START_OF_QUOTE = SimpleCommandExceptionType(new LiteralMessage("Expected quote to start a string"));

	const SimpleCommandExceptionType BuiltInExceptions::READER_EXPECTED_END_OF_QUOTE = SimpleCommandExceptionType(new LiteralMessage("Unclosed quoted string"));

	const DynamicCommandExceptionType BuiltInExceptions::READER_INVALID_ESCAPE = DynamicCommandExceptionType([](const string& character)->Message* {
		return new LiteralMessage("Invalid escape sequence '" + character + "' in quoted string");
		});

	const DynamicCommandExceptionType BuiltInExceptions::READER_INVALID_BOOL = DynamicCommandExceptionType([](const string& value)->Message* {
		return new LiteralMessage("Invalid bool, expected true or false but found '" + value + "'");
		});

	const DynamicCommandExceptionType BuiltInExceptions::READER_INVALID_INT = DynamicCommandExceptionType([](const string& value)->Message* {
		return new LiteralMessage("Invalid integer '" + value + "'");
		});

	const SimpleCommandExceptionType BuiltInExceptions::READER_EXPECTED_INT = SimpleCommandExceptionType(new LiteralMessage("Expected integer"));

	const DynamicCommandExceptionType BuiltInExceptions::READER_INVALID_LONG = DynamicCommandExceptionType([](const string& value)->Message* {
		return new LiteralMessage("Invalid long '" + value + "'");
		});

	const SimpleCommandExceptionType BuiltInExceptions::READER_EXPECTED_LONG = SimpleCommandExceptionType(new LiteralMessage("Expected long"));

	const DynamicCommandExceptionType BuiltInExceptions::READER_INVALID_DOUBLE = DynamicCommandExceptionType([](const string& value)->Message* {
		return new LiteralMessage("Invalid double '" + value + "'");
		});

	const SimpleCommandExceptionType BuiltInExceptions::READER_EXPECTED_DOUBLE = SimpleCommandExceptionType(new LiteralMessage("Expected double"));

	const DynamicCommandExceptionType BuiltInExceptions::READER_INVALID_FLOAT = DynamicCommandExceptionType([](const string& value)->Message* {
		return new LiteralMessage("Invalid float '" + value + "'");
		});

	const SimpleCommandExceptionType BuiltInExceptions::READER_EXPECTED_FLOAT = SimpleCommandExceptionType(new LiteralMessage("Expected float"));

	const SimpleCommandExceptionType BuiltInExceptions::READER_EXPECTED_BOOL = SimpleCommandExceptionType(new LiteralMessage("Expected bool"));

	const DynamicCommandExceptionType BuiltInExceptions::READER_EXPECTED_SYMBOL = DynamicCommandExceptionType([](const string& symbol)->Message* {
		return new LiteralMessage("Expected '" + symbol + "'");
		});

	const SimpleCommandExceptionType BuiltInExceptions::DISPATCHER_UNKNOWN_COMMAND = SimpleCommandExceptionType(new LiteralMessage("Unknown command"));

	const SimpleCommandExceptionType BuiltInExceptions::DISPATCHER_UNKNOWN_ARGUMENT = SimpleCommandExceptionType(new LiteralMessage("Incorrect argument for command"));

	const SimpleCommandExceptionType BuiltInExceptions::DISPATCHER_EXPECTED_ARGUMENT_SEPARATOR = SimpleCommandExceptionType(new LiteralMessage("Expected whitespace to end one argument, but found trailing data"));

	const DynamicCommandExceptionType BuiltInExceptions::DISPATCHER_PARSE_EXCEPTION = DynamicCommandExceptionType([](const string& message)->Message* {
		return new LiteralMessage("Could not parse command: " + message);
		});

}

#endif