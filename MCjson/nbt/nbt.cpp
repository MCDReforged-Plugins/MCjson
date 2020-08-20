#include "nbt.h"

using std::string;

/*
const std::string INBT::NBT_TYPES[] = { "END" ,"BYTE" ,"SHORT", "INT", "LONG", "FLOAT", "DOUBLE", "BYTE[]", "STRING", "LIST", "COMPOUND", "INT[]", "LONG[]" };

INBT::~INBT() {}

INBT* NBTBuilder::create(short id) {
	switch (id)
	{
	case 0:
		return new EndNBT();
	case 1:
		return new ByteNBT();
	case 2:
		return new ShortNBT();
	case 3:
		return new IntNBT();
	case 4:
		return new LongNBT();
	case 5:
		return new FloatNBT();
	case 6:
		return new DoubleNBT();
	case 7:
		return new ByteArrayNBT();
	case 8:
		return new StringNBT();
	case 9:
		return new ListNBT();
	case 10:
		return new CompoundNBT();
	case 11:
		return new IntArrayNBT();
	case 12:
		return new LongArrayNBT();
	default:
		return NULL;
	}
}

std::string NBTBuilder::getTypeName(short id) {
	switch (id)
	{
	case 0:
		return "TAG_End";
	case 1:
		return "TAG_Byte";
	case 2:
		return "TAG_Short";
	case 3:
		return "TAG_Int";
	case 4:
		return "TAG_Long";
	case 5:
		return "TAG_Float";
	case 6:
		return "TAG_Double";
	case 7:
		return "TAG_Byte_Array";
	case 8:
		return "TAG_String";
	case 9:
		return "TAG_List";
	case 10:
		return "TAG_Compound";
	case 11:
		return "TAG_Int_Array";
	case 12:
		return "TAG_Long_Array";
	case 99:
		return "Any Numeric Tag";
	default:
		return "UNKNOWN";
	}
}

short EndNBT::getId() const { return 0; }

INBT* EndNBT::copy() const { return new EndNBT(); }

bool EndNBT::equals(INBT* ptr) const { return dynamic_cast<EndNBT*>(ptr); }
*/