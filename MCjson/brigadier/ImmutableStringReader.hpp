#ifndef brigadier_HPP_ImmutableStringReader
#define brigadier_HPP_ImmutableStringReader

#include <string>
//using std::string;

namespace brigadier {
	// Subset of https://github.com/Mojang/brigadier/blob/master/src/main/java/com/mojang/brigadier/ImmutableStringReader.java
	class ImmutableStringReader {
	public:
		virtual std::string getString() const = 0;
		virtual int getRemainingLength() const = 0;
		virtual int getTotalLength() const = 0;
		virtual int getCursor() const = 0;
		virtual std::string getRead() const = 0;
		virtual std::string getRemaining() const = 0;
		virtual bool canRead(int var1) const = 0;
		virtual bool canRead() const = 0;
		virtual char peek() const = 0;
		virtual char peek(int var1) const = 0;
	};
}

#endif