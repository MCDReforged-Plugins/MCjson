#ifndef brigadier_HPP_ImmutableStringReader
#define brigadier_HPP_ImmutableStringReader

#include <string>
//using std::string;

namespace brigadier {
	// Subset of https://github.com/Mojang/brigadier/blob/master/src/main/java/com/mojang/brigadier/ImmutableStringReader.java
	class ImmutableStringReader {
	public:
		virtual std::string getString() = 0;
		virtual int getRemainingLength() = 0;
		virtual int getTotalLength() = 0;
		virtual int getCursor() = 0;
		virtual std::string getRead() = 0;
		virtual std::string getRemaining() = 0;
		virtual bool canRead(int var1) = 0;
		virtual bool canRead() = 0;
		virtual char peek() = 0;
		virtual char peek(int var1) = 0;
	};
}

#endif