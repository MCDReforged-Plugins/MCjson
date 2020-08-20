#ifndef brigadier_HPP_BuiltInExceptions

#include "Exception.hpp"

namespace brigadier {

	
	class BuiltInExceptionProvider {
	public:
		virtual Dynamic2CommandExceptionType doubleTooLow() const = 0;
		virtual Dynamic2CommandExceptionType doubleTooHigh() const = 0;
		virtual Dynamic2CommandExceptionType floatTooLow() const = 0;
		virtual Dynamic2CommandExceptionType floatTooHigh() const = 0;
		virtual Dynamic2CommandExceptionType integerTooLow() const = 0;
		virtual Dynamic2CommandExceptionType integerTooHigh() const = 0;
		virtual Dynamic2CommandExceptionType longTooLow() const = 0;
		virtual Dynamic2CommandExceptionType longTooHigh() const = 0;
		virtual DynamicCommandExceptionType literalIncorrect() const = 0;
		virtual SimpleCommandExceptionType readerExpectedStartOfQuote() const = 0;
		virtual SimpleCommandExceptionType readerExpectedEndOfQuote() const = 0;
		virtual DynamicCommandExceptionType readerInvalidEscape() const = 0;
		virtual DynamicCommandExceptionType readerInvalidBool() const = 0;
		virtual DynamicCommandExceptionType readerInvalidInt() const = 0;
		virtual SimpleCommandExceptionType readerExpectedInt() const = 0;
		virtual DynamicCommandExceptionType readerInvalidLong() const = 0;
		virtual SimpleCommandExceptionType readerExpectedLong() const = 0;
		virtual DynamicCommandExceptionType readerInvalidDouble() const = 0;
		virtual SimpleCommandExceptionType readerExpectedDouble() const = 0;
		virtual DynamicCommandExceptionType readerInvalidFloat() const = 0;
		virtual SimpleCommandExceptionType readerExpectedFloat() const = 0;
		virtual SimpleCommandExceptionType readerExpectedBool() const = 0;
		virtual DynamicCommandExceptionType readerExpectedSymbol() const = 0;
		virtual SimpleCommandExceptionType dispatcherUnknownCommand() const = 0;
		virtual SimpleCommandExceptionType dispatcherUnknownArgument() const = 0;
		virtual SimpleCommandExceptionType dispatcherExpectedArgumentSeparator() const = 0;
		virtual DynamicCommandExceptionType dispatcherParseException() const = 0;
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
		Dynamic2CommandExceptionType doubleTooLow() const override;
		Dynamic2CommandExceptionType doubleTooHigh() const override;
		Dynamic2CommandExceptionType floatTooLow() const override;
		Dynamic2CommandExceptionType floatTooHigh() const override;
		Dynamic2CommandExceptionType integerTooLow() const override;
		Dynamic2CommandExceptionType integerTooHigh() const override;
		Dynamic2CommandExceptionType longTooLow() const override;
		Dynamic2CommandExceptionType longTooHigh() const override;
		DynamicCommandExceptionType literalIncorrect() const override;
		SimpleCommandExceptionType readerExpectedStartOfQuote() const override;
		SimpleCommandExceptionType readerExpectedEndOfQuote() const override;
		DynamicCommandExceptionType readerInvalidEscape() const override;
		DynamicCommandExceptionType readerInvalidBool() const override;
		DynamicCommandExceptionType readerInvalidInt() const override;
		SimpleCommandExceptionType readerExpectedInt() const override;
		DynamicCommandExceptionType readerInvalidLong() const override;
		SimpleCommandExceptionType readerExpectedLong() const override;
		DynamicCommandExceptionType readerInvalidDouble() const override;
		SimpleCommandExceptionType readerExpectedDouble() const override;
		DynamicCommandExceptionType readerInvalidFloat() const override;
		SimpleCommandExceptionType readerExpectedFloat() const override;
		SimpleCommandExceptionType readerExpectedBool() const override;
		DynamicCommandExceptionType readerExpectedSymbol() const override;
		SimpleCommandExceptionType dispatcherUnknownCommand() const override;
		SimpleCommandExceptionType dispatcherUnknownArgument() const override;
		SimpleCommandExceptionType dispatcherExpectedArgumentSeparator() const override;
		DynamicCommandExceptionType dispatcherParseException() const override;
	};

#ifdef brigadier_IMPLEMENTS

	const Dynamic2CommandExceptionType BuiltInExceptions::DOUBLE_TOO_SMALL = Dynamic2CommandExceptionType([](const std::string& found, const std::string& min)->Message* {
		return new LiteralMessage("Double must not be less than " + min + ", found " + found); 
		});

	const Dynamic2CommandExceptionType BuiltInExceptions::DOUBLE_TOO_BIG = Dynamic2CommandExceptionType([](const std::string& found, const std::string& max)->Message* {
		return new LiteralMessage("Double must not be more than " + max + ", found " + found);
		});

	const Dynamic2CommandExceptionType BuiltInExceptions::FLOAT_TOO_SMALL = Dynamic2CommandExceptionType([](const std::string& found, const std::string& min)->Message* {
		return new LiteralMessage("Float must not be less than " + min + ", found " + found);
		});

	const Dynamic2CommandExceptionType BuiltInExceptions::FLOAT_TOO_BIG = Dynamic2CommandExceptionType([](const std::string& found, const std::string& max)->Message* {
		return new LiteralMessage("Float must not be more than " + max + ", found " + found);
		});

	const Dynamic2CommandExceptionType BuiltInExceptions::INTEGER_TOO_SMALL = Dynamic2CommandExceptionType([](const std::string& found, const std::string& min)->Message* {
		return new LiteralMessage("Integer must not be less than " + min + ", found " + found);
		});

	const Dynamic2CommandExceptionType BuiltInExceptions::INTEGER_TOO_BIG = Dynamic2CommandExceptionType([](const std::string& found, const std::string& max)->Message* {
		return new LiteralMessage("Integer must not be more than " + max + ", found " + found);
		});

	const Dynamic2CommandExceptionType BuiltInExceptions::LONG_TOO_SMALL = Dynamic2CommandExceptionType([](const std::string& found, const std::string& min)->Message* {
		return new LiteralMessage("Long must not be less than " + min + ", found " + found);
		});

	const Dynamic2CommandExceptionType BuiltInExceptions::LONG_TOO_BIG = Dynamic2CommandExceptionType([](const std::string& found, const std::string& max)->Message* {
		return new LiteralMessage("Long must not be more than " + max + ", found " + found);
		});
	
	const DynamicCommandExceptionType BuiltInExceptions::LITERAL_INCORRECT = DynamicCommandExceptionType([](const std::string& expected)->Message* {
		return new LiteralMessage("Expected literal " + expected); 
		});

	const SimpleCommandExceptionType BuiltInExceptions::READER_EXPECTED_START_OF_QUOTE = SimpleCommandExceptionType(new LiteralMessage("Expected quote to start a string"));

	const SimpleCommandExceptionType BuiltInExceptions::READER_EXPECTED_END_OF_QUOTE = SimpleCommandExceptionType(new LiteralMessage("Unclosed quoted string"));

	const DynamicCommandExceptionType BuiltInExceptions::READER_INVALID_ESCAPE = DynamicCommandExceptionType([](const std::string& character)->Message* {
		return new LiteralMessage("Invalid escape sequence '" + character + "' in quoted string");
		});

	const DynamicCommandExceptionType BuiltInExceptions::READER_INVALID_BOOL = DynamicCommandExceptionType([](const std::string& value)->Message* {
		return new LiteralMessage("Invalid bool, expected true or false but found '" + value + "'");
		});

	const DynamicCommandExceptionType BuiltInExceptions::READER_INVALID_INT = DynamicCommandExceptionType([](const std::string& value)->Message* {
		return new LiteralMessage("Invalid integer '" + value + "'");
		});

	const SimpleCommandExceptionType BuiltInExceptions::READER_EXPECTED_INT = SimpleCommandExceptionType(new LiteralMessage("Expected integer"));

	const DynamicCommandExceptionType BuiltInExceptions::READER_INVALID_LONG = DynamicCommandExceptionType([](const std::string& value)->Message* {
		return new LiteralMessage("Invalid long '" + value + "'");
		});

	const SimpleCommandExceptionType BuiltInExceptions::READER_EXPECTED_LONG = SimpleCommandExceptionType(new LiteralMessage("Expected long"));

	const DynamicCommandExceptionType BuiltInExceptions::READER_INVALID_DOUBLE = DynamicCommandExceptionType([](const std::string& value)->Message* {
		return new LiteralMessage("Invalid double '" + value + "'");
		});

	const SimpleCommandExceptionType BuiltInExceptions::READER_EXPECTED_DOUBLE = SimpleCommandExceptionType(new LiteralMessage("Expected double"));

	const DynamicCommandExceptionType BuiltInExceptions::READER_INVALID_FLOAT = DynamicCommandExceptionType([](const std::string& value)->Message* {
		return new LiteralMessage("Invalid float '" + value + "'");
		});

	const SimpleCommandExceptionType BuiltInExceptions::READER_EXPECTED_FLOAT = SimpleCommandExceptionType(new LiteralMessage("Expected float"));

	const SimpleCommandExceptionType BuiltInExceptions::READER_EXPECTED_BOOL = SimpleCommandExceptionType(new LiteralMessage("Expected bool"));

	const DynamicCommandExceptionType BuiltInExceptions::READER_EXPECTED_SYMBOL = DynamicCommandExceptionType([](const std::string& symbol)->Message* {
		return new LiteralMessage("Expected '" + symbol + "'");
		});

	const SimpleCommandExceptionType BuiltInExceptions::DISPATCHER_UNKNOWN_COMMAND = SimpleCommandExceptionType(new LiteralMessage("Unknown command"));

	const SimpleCommandExceptionType BuiltInExceptions::DISPATCHER_UNKNOWN_ARGUMENT = SimpleCommandExceptionType(new LiteralMessage("Incorrect argument for command"));

	const SimpleCommandExceptionType BuiltInExceptions::DISPATCHER_EXPECTED_ARGUMENT_SEPARATOR = SimpleCommandExceptionType(new LiteralMessage("Expected whitespace to end one argument, but found trailing data"));

	const DynamicCommandExceptionType BuiltInExceptions::DISPATCHER_PARSE_EXCEPTION = DynamicCommandExceptionType([](const std::string& message)->Message* {
		return new LiteralMessage("Could not parse command: " + message);
		});


	Dynamic2CommandExceptionType BuiltInExceptions::doubleTooLow() const { return DOUBLE_TOO_SMALL; }
	Dynamic2CommandExceptionType BuiltInExceptions::doubleTooHigh() const { return DOUBLE_TOO_BIG; }
	Dynamic2CommandExceptionType BuiltInExceptions::floatTooLow() const { return FLOAT_TOO_SMALL; }
	Dynamic2CommandExceptionType BuiltInExceptions::floatTooHigh() const { return FLOAT_TOO_BIG; }
	Dynamic2CommandExceptionType BuiltInExceptions::integerTooLow() const { return INTEGER_TOO_SMALL; }
	Dynamic2CommandExceptionType BuiltInExceptions::integerTooHigh() const { return INTEGER_TOO_BIG; }
	Dynamic2CommandExceptionType BuiltInExceptions::longTooLow() const { return LONG_TOO_SMALL; }
	Dynamic2CommandExceptionType BuiltInExceptions::longTooHigh() const { return LONG_TOO_BIG; }
	DynamicCommandExceptionType BuiltInExceptions::literalIncorrect() const { return LITERAL_INCORRECT; }
	SimpleCommandExceptionType BuiltInExceptions::readerExpectedStartOfQuote() const { return READER_EXPECTED_START_OF_QUOTE; }
	SimpleCommandExceptionType BuiltInExceptions::readerExpectedEndOfQuote() const { return READER_EXPECTED_END_OF_QUOTE; }
	DynamicCommandExceptionType BuiltInExceptions::readerInvalidEscape() const { return READER_INVALID_ESCAPE; }
	DynamicCommandExceptionType BuiltInExceptions::readerInvalidBool() const { return READER_INVALID_BOOL; }
	DynamicCommandExceptionType BuiltInExceptions::readerInvalidInt() const { return READER_INVALID_INT; }
	SimpleCommandExceptionType BuiltInExceptions::readerExpectedInt() const { return READER_EXPECTED_INT; }
	DynamicCommandExceptionType BuiltInExceptions::readerInvalidLong() const  { return READER_INVALID_LONG; }
	SimpleCommandExceptionType BuiltInExceptions::readerExpectedLong() const { return READER_EXPECTED_LONG; }
	DynamicCommandExceptionType BuiltInExceptions::readerInvalidDouble() const { return READER_INVALID_DOUBLE; }
	SimpleCommandExceptionType BuiltInExceptions::readerExpectedDouble() const { return READER_EXPECTED_DOUBLE; }
	DynamicCommandExceptionType BuiltInExceptions::readerInvalidFloat() const { return READER_INVALID_FLOAT; }
	SimpleCommandExceptionType BuiltInExceptions::readerExpectedFloat() const { return READER_EXPECTED_FLOAT; }
	SimpleCommandExceptionType BuiltInExceptions::readerExpectedBool() const { return READER_EXPECTED_BOOL; }
	DynamicCommandExceptionType BuiltInExceptions::readerExpectedSymbol() const { return READER_EXPECTED_SYMBOL; }
	SimpleCommandExceptionType BuiltInExceptions::dispatcherUnknownCommand() const { return DISPATCHER_UNKNOWN_COMMAND; }
	SimpleCommandExceptionType BuiltInExceptions::dispatcherUnknownArgument() const { return DISPATCHER_UNKNOWN_ARGUMENT; }
	SimpleCommandExceptionType BuiltInExceptions::dispatcherExpectedArgumentSeparator() const { return DISPATCHER_EXPECTED_ARGUMENT_SEPARATOR; }
	DynamicCommandExceptionType BuiltInExceptions::dispatcherParseException() const { return DISPATCHER_PARSE_EXCEPTION; }

#endif

}

#define brigadier_HPP_BuiltInExceptions
#endif