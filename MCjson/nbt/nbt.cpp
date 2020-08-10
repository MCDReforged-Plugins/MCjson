#include "nbt.h"

using std::string;

string INBT::getString() {
	return this->toString();
}

INBT* NBTBuilder::create(char id) { return 0; }