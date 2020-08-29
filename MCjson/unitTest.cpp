//#define BOOST_PYTHON_STATIC_LIB

#include<iostream>
#include<exception>
//#include "include/brigadier.hpp"
//#include "nbt/JsonToNBT.cpp"
//#include "brigadier/brigadier.h"
#include "MCjson.h"
#include <boost/foreach.hpp>

using std::string;
using std::cout;
using std::endl;

class str;
class Test;
class Test2;
class Test3;
class Test4;
boost::python::object test(boost::python::str);
void test2();
template<class T>
void pure_cout(T s);

class str {
private:
	string s;
public:
	str(string s): s(s) {}
	void show() { cout << this->s << endl; }
};

class Test {
public:
	virtual const void show() {};
	virtual ~Test() {};
	virtual Test* clone() { return 0; };
};

class Test2 : public Test {
private:
	int num;
public:
	Test2(const Test2& outher) { this->num = outher.num; }
	Test2(int i) { this->num = i; }
	void const show() { cout << this->num << endl; }
	~Test2() { cout << "~Test2" << endl; }
	Test* clone() { return new Test2(*this); }
};

typedef void (*Function)(int);
class Test3 {
private:
	Function func = 0;
public:
	Test3(void (*function)(int)) { this->func = function; };
	void do_func() { this->func(1); }
};

class Test4 {
private:
	static const Test3* func_class;
public:
	void call() { const_cast<Test3*>(this->func_class)->do_func(); }
};

const Test3* Test4::func_class = new Test3([](int input) {cout << "call_int: " << input << endl; });


boost::python::object test(boost::python::str s) {
	brigadier::StringReader* reader = new brigadier::StringReader(string(boost::python::extract<char*>(s)));
	JsonToNBT tools(reader);
	try {
		boost::python::dict result = tools.readStruct();
		return result;
	}
	catch (brigadier::Exception& e) {
		cout << "[" << e.getTypeString() << "] " << e.getMessage() << endl;
	}
	return boost::python::object();
}

void test2() {
	for (int count = 1; count <= 10000; count++) {
		brigadier::StringReader* reader = new brigadier::StringReader("xxx");
		reader->setCursor(2);
		try {
			brigadier::LiteralMessage* message = new brigadier::LiteralMessage("ERROR_TRAILING_DATA");
			brigadier::SimpleCommandExceptionType exception_type(message);
			brigadier::CommandSyntaxException exception = exception_type.createWithContext(reader);
			throw exception;
		}
		catch (brigadier::Exception& e) {
			cout << e.getMessage() << endl;
		}
		delete(reader);
	}
}

template<class T>
void pure_cout(T s) {
	cout << "[C output] " << s << endl;;
}

int dll_call() {

	string s("{Brain: {memories: {}}, HurtByTimestamp: 0, SleepTimer: 0s, Attributes: [{Base: 20.0d, Name: \"generic.maxHealth\"}, {Base: 0.0d, Name: \"generic.knockbackResistance\"}, {Base: 0.10000000149011612d, Name: \"generic.movementSpeed\"}, {Base: 0.0d, Name: \"generic.armor\"}, {Base: 0.0d, Name: \"generic.armorToughness\"}, {Base: 1.0d, Name: \"generic.attackDamage\"}, {Base: 4.0d, Name: \"generic.attackSpeed\"}, {Base: 0.0d, Name: \"generic.luck\"}], Invulnerable: 0b, FallFlying: 0b, PortalCooldown: 0, AbsorptionAmount: 0.0f, abilities: {invulnerable: 1b, mayfly: 1b, instabuild: 1b, walkSpeed: 0.1f, mayBuild: 1b, flying: 0b, flySpeed: 0.05f}, FallDistance: 0.0f, recipeBook: {recipes: [\"minecraft:wooden_pickaxe\", \"minecraft:campfire\", \"minecraft:ladder\", \"minecraft:wooden_sword\", \"minecraft:wooden_shovel\", \"minecraft:crossbow\", \"minecraft:dispenser\", \"minecraft:wooden_axe\", \"minecraft:wooden_hoe\"], isFilteringCraftable: 0b, toBeDisplayed: [\"minecraft:wooden_pickaxe\", \"minecraft:campfire\", \"minecraft:ladder\", \"minecraft:wooden_sword\", \"minecraft:wooden_shovel\", \"minecraft:crossbow\", \"minecraft:dispenser\", \"minecraft:wooden_axe\", \"minecraft:wooden_hoe\"], isFurnaceGuiOpen: 0b, isGuiOpen: 0b, isFurnaceFilteringCraftable: 0b}, DeathTime: 0s, XpSeed: -1451274418, XpTotal: 0, playerGameType: 1, SelectedItem: {id: \"minecraft:stick\", Count: 1b, tag: {RepairCost: 0, display: {Name: '{\"text\":\"kunkunkun\\\\\"\\'\\\\\\\\/?..\"}'}}}, seenCredits: 0b, Motion: [0.0d, -0.0784000015258789d, 0.0d], UUIDLeast: -7682871655027289500L, Health: 20.0f, foodSaturationLevel: 5.0f, Air: 300s, OnGround: 1b, Dimension: 0, Rotation: [-103.37291f, 24.449465f], XpLevel: 0, Score: 0, UUIDMost: -8956407710851122068L, Pos: [12.84031607145009d, 4.0d, 102.86007088819247d], Fire: -20s, XpP: 0.0f, EnderItems: [{Slot: 0b, id: \"minecraft:tnt\", Count: 1b}, {Slot: 1b, id: \"minecraft:torch\", Count: 1b, tag: {RepairCost: 0, display: {Name: '{\"text\":\"reeeeee\"}'}}}], DataVersion: 2230, foodLevel: 20, foodExhaustionLevel: 0.0f, HurtTime: 0s, SelectedItemSlot: 3, Inventory: [{Slot: 0b, id: \"minecraft:ender_chest\", Count: 1b}, {Slot: 1b, id: \"minecraft:anvil\", Count: 1b}, {Slot: 2b, id: \"minecraft:bow\", Count: 1b, tag: {Damage: 0}}, {Slot: 3b, id: \"minecraft:stick\", Count: 1b, tag: {RepairCost: 0, display: {Name: '{\"text\":\"kunkunkun\\\\\"\\'\\\\\\\\/?..\"}'}}}, {Slot: 4b, id: \"minecraft:stick\", Count: 1b, tag: {RepairCost: 0, display: {Name: '{\"text\":\"kunkunkun\\\\\"\\'\\\\\\\\/?..\"}'}}}], foodTickTimer: 0}");
	/*
	brigadier::StringReader reader("{\"key\":\"reeeeee\"}");
	cout << reader.peek() << endl;
	*/
	boost::python::str py_str = s.c_str();
	boost::python::object result = test(py_str);
	

	cout << "ok" << endl;
	return 0;
}